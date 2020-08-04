using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;


namespace ImageCreator
{
    class Program
    {
        const uint FreeCluster = 0xFFFFFFFF;
        const uint EndOfClusterChain = 0xFFFFFFFE;
        const uint BadCluster = 0xFFFFFFFD;
        const uint ReservedCluster = 0xFFFFFFFC;


        static string filename;
        static string bootsectorfilename;

        static Stream image;
        static BinaryWriter imagewriter;

        static string rootdirectory;
        static bool trim = false;
        static FileSystemDefinition filesystemdefinition;

        static byte[] sector;
        static byte[] cluster;


        static void Main(string[] args)
        {
            filesystemdefinition = new FileSystemDefinition();

            for (int i = 0; i < args.Length; ++i)
            {
                switch (args[i])
                {
                    case "-rootdirectory":
                        rootdirectory = args[i + 1];
                        i++;
                        break;

                    case "-image":
                        filename = args[i + 1];
                        i++;
                        break;

                    case "-bootsector":
                        bootsectorfilename = args[i + 1];
                        i++;
                        break;

                    case "-SectorSizeInBytes":
                        if (!int.TryParse(args[i + 1], out filesystemdefinition.SectorSizeInBytes))
                        {
                            filesystemdefinition.SectorSizeInBytes = 512;
                        }

                        i++;
                        break;

                    case "-SectorCount":
                        if (!uint.TryParse(args[i + 1], out filesystemdefinition.SectorCount))
                        {
                            filesystemdefinition.SectorCount = 2880;
                        }

                        i++;
                        break;

                    case "-ClusterSizeInBytes":
                        if (!int.TryParse(args[i + 1], out filesystemdefinition.ClusterSizeInBytes))
                        {
                            filesystemdefinition.ClusterSizeInBytes = 4096;
                        }

                        i++;
                        break;

                    case "-trim":
                        trim = true;
                        break;
                }
            }

            //Initialize the rest of the file system definition parameters
            filesystemdefinition.CalculateParameters();

            //These will be used to more or less simulate the access of a real device
            sector = new byte[filesystemdefinition.SectorSizeInBytes];
            cluster = new byte[filesystemdefinition.ClusterSizeInBytes];

            //These are the actual image streams
            //image = File.Create(filename);
            image = new MemoryStream();
            imagewriter = new BinaryWriter(image);

            //Save the boot sector to the begining of the disk. Because the
            //boot sector has to be 512 bytes for the BIOS to load it, we
            //simply read the first 512 bytes of the boot sector image file
            //and write that to the first 512 bytes of the file system.
            FileStream bootsector = File.Open(bootsectorfilename, FileMode.Open, FileAccess.Read);
            byte[] bootsectordata = new byte[512];
            bootsector.Read(bootsectordata, 0, 512);
            bootsector.Close();
            image.Write(bootsectordata, 0, bootsectordata.Length);

            //Seek to sector 1 (second sector)
            image.Seek(filesystemdefinition.SectorSizeInBytes, SeekOrigin.Begin);

            //Write the file system definition to the disk
            byte[] filesystemdefinitionbytes = filesystemdefinition.ToBytes();
            image.Write(filesystemdefinitionbytes, 0, filesystemdefinitionbytes.Length);

            //Seek to sector 4 (fifth sector) in the file system
            image.Seek(4 * filesystemdefinition.SectorSizeInBytes, SeekOrigin.Begin);

            //Write the CAT.
            //First entry in the CAT (entry 0x0) is the root directory which has
            //to be set to EndOfClusterChain.
            imagewriter.Write(EndOfClusterChain);

            //The rest of the entries have to be set to FreeCluster
            for (int i = 0; i < filesystemdefinition.ClusterCount; ++i)
                imagewriter.Write(FreeCluster);

            //End of the file system creation
            //image.SetLength(filesystemdefinition.SectorCount * filesystemdefinition.SectorSizeInBytes);

            imagewriter.Flush();
            imagewriter.Seek(0, SeekOrigin.Begin);

            List<string> directories = new List<string>(Directory.GetDirectories(rootdirectory, "*", SearchOption.AllDirectories));

            for (int i = 0; i < directories.Count; ++i)
            {
                CreateDirectory(directories[i].Replace('\\', '/').Replace(rootdirectory + '/', ""));
            }

            List<string> files = new List<string>(Directory.GetFiles(rootdirectory, "*", SearchOption.AllDirectories));

            for (int i = 0; i < files.Count; ++i)
            {
                string file = files[i].Replace('\\', '/').Replace(rootdirectory + '/', "");
                AddFile(files[i], file);
            }

            File.WriteAllBytes(filename, ((MemoryStream)image).ToArray());
        }

        /*
         * Common functions for use in manipulating the file system
         */

        //This takes in a sector number (base 0) and gives out the offset in
        //bytes of that sector
        private static uint SectorNumberToByteOffset(uint sectorNumber)
        {
            return sectorNumber * (uint)filesystemdefinition.SectorSizeInBytes;
        }

        //This takes in a CAT number (base 0) and gives out the offset in
        //bytes of that CAT number. We ues the following formula:
        //offset = (1 + 3) * SectorSizeInBytes + catNumber * 4
        private static uint CatNumberToByteOffset(uint catNumber)
        {
            return (1 + 3) * (uint)filesystemdefinition.SectorSizeInBytes + catNumber * 4;
        }

        //This takes in a CAT number (base 0) and gives out the offset in
        //sectors (base 0) of that CAT number.
        private static uint CatNumberToSectorOffset(uint catNumber)
        {
            //The first 4 sectors are automatically reserved. After that the
            //CAT entries begin. We are doing integer division so the result
            //is automatically rounded down like we want.
            return (1 + 3) + ((catNumber * 4) / (uint)filesystemdefinition.SectorSizeInBytes);
        }

        //This takes a cat number and gives out the offset of that cat number
        //into the sector it resides in. If the cat entry lies on a sector
        //boundary than zero is returned.
        private static uint CatNumberOffsetIntoSector(uint catNumber)
        {
            return CatNumberToByteOffset(catNumber) - (CatNumberToSectorOffset(catNumber) * (uint)filesystemdefinition.SectorSizeInBytes);
        }

        //This takes a cat sector number (cat sectors start counting
        //from 0 at the begining of the CAT and a byte offset into
        //that sector and gives out the cat number (cat entry).
        private static uint CatNumberFromCatSectorAndOffsetIntoSector(uint sectorNumber, uint offsetIntoSector)
        {
            //Get the number of CAT entries that exist in each sector
            uint catentriespersector = (uint)filesystemdefinition.SectorSizeInBytes / 4;

            //NO LONGER TRUE!!!
            //Here we are taking the sectorNumber and subtracting 4 because
            //the first 4 sectors are already used. We than multiply by the
            //number of CAT entries per sector.
            uint result = sectorNumber * catentriespersector;

            //Now we take into account the offset into the sector. Each CAT
            //entry is four bytes big so just divide the offset by four.
            result += (offsetIntoSector / 4);

            //Return the result
            return result;
        }

        //This takes a cluster number (base 0) and gives out the offset in
        //bytes of that cluster
        private static long ClusterNumberToByteOffset(uint clusterNumber)
        {
            return filesystemdefinition.DataOffsetInBytes + (clusterNumber * filesystemdefinition.ClusterSizeInBytes);
        }

        //This is meant to simulate reading a sector from a device
        private static void ReadSector(uint sectorNumber)
        {
            image.Seek(SectorNumberToByteOffset(sectorNumber), SeekOrigin.Begin);
            image.Read(sector, 0, sector.Length);
        }

        //THIS NEEDS TO BE CHECKED AGAIN FOR ERRORS
        //IT DOES NOT APPEAR THAT THIS FUNCTION READS
        //ON A SECTOR BOUNDARY
        //This is meant to simulate reading a cat sector from a device
        private static void ReadCatSector(uint catNumber)
        {
            //image.Seek(CatNumberToByteOffset(catNumber), SeekOrigin.Begin);
            image.Seek(CatNumberToSectorOffset(catNumber) * filesystemdefinition.SectorSizeInBytes, SeekOrigin.Begin);
            image.Read(sector, 0, sector.Length);
        }

        //This is meant to simulate reading an entire cluster from a device
        private static void ReadCluster(uint clusterNumber)
        {
            image.Seek(ClusterNumberToByteOffset(clusterNumber), SeekOrigin.Begin);
            image.Read(cluster, 0, cluster.Length);
        }

        //This is meant to simulate writing a sector to a device
        private static void WriteSector(uint sectorNumber, byte[] sectorData)
        {
            if (image.Length < SectorNumberToByteOffset(sectorNumber) + filesystemdefinition.SectorSizeInBytes)
            {
                image.SetLength(SectorNumberToByteOffset(sectorNumber) + filesystemdefinition.SectorSizeInBytes);
            }

            image.Seek(SectorNumberToByteOffset(sectorNumber), SeekOrigin.Begin);
            image.Write(sectorData, 0, sectorData.Length);
        }

        //THIS NEEDS TO BE CHECKED AGAIN FOR ERRORS
        //IT DOES NOT APPEAR THAT THIS FUNCTION READS
        //ON A SECTOR BOUNDARY
        //This is meant to simulate writing an entire cat sector
        private static void WriteCatSector(uint catNumber, byte[] sectorData)
        {
            //image.Seek(CatNumberToByteOffset(catNumber), SeekOrigin.Begin);
            image.Seek(CatNumberToSectorOffset(catNumber) * filesystemdefinition.SectorSizeInBytes, SeekOrigin.Begin);
            image.Write(sectorData, 0, sectorData.Length);
        }

        //This is meant to simulate writing an entire cluster
        private static void WriteCluster(uint clusterNumber, byte[] clusterData)
        {
            if (image.Length < ClusterNumberToByteOffset(clusterNumber) + filesystemdefinition.ClusterSizeInBytes)
            {
                image.SetLength(ClusterNumberToByteOffset(clusterNumber) + filesystemdefinition.ClusterSizeInBytes);
            }

            image.Seek(ClusterNumberToByteOffset(clusterNumber), SeekOrigin.Begin);
            image.Write(clusterData, 0, clusterData.Length);
        }

        //This is meant to simulate writing part of a cluster
        private static void WriteCluster(uint clusterNumber, byte[] clusterData, int offset, int count)
        {
            if (image.Length < clusterNumber * filesystemdefinition.ClusterSizeInBytes)
            {
                image.SetLength(clusterNumber * filesystemdefinition.ClusterSizeInBytes);
            }

            image.Seek(ClusterNumberToByteOffset(clusterNumber), SeekOrigin.Begin);
            image.Write(clusterData, offset, count);
        }

        private static uint FindFreeCluster()
        {
            return FindFreeClusters(1)[0];
        }

        private static uint[] FindFreeClusters(int count)
        {
            List<uint> clusters = new List<uint>(count);

            for (uint i = 0; i < filesystemdefinition.CatSizeInSectors; ++i)
            {
                ReadSector((uint)(4 + i));
                
                for (uint j = 0; j < filesystemdefinition.SectorSizeInBytes; j += 4)
                {
                    uint fatentry = BitConverter.ToUInt32(sector, (int)j);

                    if (fatentry == FreeCluster)
                    {
                        clusters.Add(CatNumberFromCatSectorAndOffsetIntoSector(i, j));
                        count--;

                        if (count < 1)
                            break;
                    }
                }

                if (count < 1)
                    break;
            }

            return clusters.ToArray();
        }

        private static void WriteClusterChain(params uint[] clusters)
        {
            for (int i = 0; i < clusters.Length; ++i)
            {
                ReadCatSector(clusters[i]);
                
                if (i != clusters.Length - 1)
                {
                    byte[] value = BitConverter.GetBytes(clusters[i + 1]);
                    sector[CatNumberOffsetIntoSector(clusters[i])] = value[0];
                    sector[CatNumberOffsetIntoSector(clusters[i]) + 1] = value[1];
                    sector[CatNumberOffsetIntoSector(clusters[i]) + 2] = value[2];
                    sector[CatNumberOffsetIntoSector(clusters[i]) + 3] = value[3];
                }
                else
                {
                    sector[CatNumberOffsetIntoSector(clusters[i])] = 0xFE;
                    sector[CatNumberOffsetIntoSector(clusters[i]) + 1] = 0xFF;
                    sector[CatNumberOffsetIntoSector(clusters[i]) + 2] = 0xFF;
                    sector[CatNumberOffsetIntoSector(clusters[i]) + 3] = 0xFF;
                }
                
                WriteCatSector(clusters[i], sector);
            }
        }

        private static void WriteData(byte[] data, params uint[] clusters)
        {
            for (int i = 0; i < clusters.Length; ++i)
            {
                int bytestowrite = filesystemdefinition.ClusterSizeInBytes;

                if (data.Length - (i * filesystemdefinition.ClusterSizeInBytes) < filesystemdefinition.ClusterSizeInBytes)
                    bytestowrite = (data.Length - (i * filesystemdefinition.ClusterSizeInBytes)) % filesystemdefinition.ClusterSizeInBytes;

                WriteCluster(clusters[i], data, i * filesystemdefinition.ClusterSizeInBytes, bytestowrite);
            }
        }

        private static uint ExpandDirectoryCluster(uint lastDirectoryCluster)
        {
            uint cluster = FindFreeCluster();
            ClearCluster(cluster);
            WriteClusterChain(lastDirectoryCluster, cluster);

            return cluster;
        }

        private static void WriteDirectoryEntryToDirectory(uint firstDirectoryCluster, ref DirectoryEntry entry)
        {
            uint currentcluster = firstDirectoryCluster;

            while (true)
            {
                ReadCluster(currentcluster);

                for (int i = 0; i < filesystemdefinition.ClusterSizeInBytes; i += 64)
                {
                    if (cluster[i] == 0)
                    {
                        Array.Copy(entry.ToBytes(), 0, cluster, i, 64);
                        WriteCluster(currentcluster, cluster);

                        return;
                    }
                }

                uint nextcluster = GetNextClusterInChain(currentcluster);

                if (nextcluster == EndOfClusterChain)
                    currentcluster = ExpandDirectoryCluster(currentcluster);
                else
                    currentcluster = nextcluster;
            }
        }

        private static uint GetNextClusterInChain(uint catNumber)
        {
            ReadCatSector(catNumber);
            return BitConverter.ToUInt32(sector, (int)CatNumberOffsetIntoSector(catNumber));
        }

        private static void ClearCluster(uint clusterToClear)
        {
            byte[] cluster = new byte[filesystemdefinition.ClusterSizeInBytes];

            for (int i = 0; i < cluster.Length; ++i)
            {
                cluster[i] = 0;
            }

            WriteCluster(clusterToClear, cluster);
        }

        private static void CreateDirectory(string directory)
        {
            string[] directories = directory.Split('/');

            uint currentcluster = 0;
            int current = 0;

            while (true)
            {
            StartLoop:
                ReadCluster(currentcluster);

            for (int i = 0; i < filesystemdefinition.ClusterSizeInBytes; i += 64)
                {
                    if ((cluster[i] & 0x3) == 1)
                    {
                        string str = ASCIIEncoding.ASCII.GetString(cluster, i + 32, 32);
                        str = str.TrimEnd('\0');

                        if (str == directories[current])
                        {
                            current++;

                            if (current > directories.Length - 1)
                            {
                                return;
                            }

                            currentcluster = BitConverter.ToUInt32(cluster, i + 1);
                            goto StartLoop;
                        }
                    }
                }

                uint nextcluster = GetNextClusterInChain(currentcluster);

                if (nextcluster == (uint)0xFFFFFFFE)
                {
                    uint free = FindFreeCluster();
                    ClearCluster(free);
                    WriteClusterChain(free);

                    DirectoryEntry entry = new DirectoryEntry();
                    entry.Attributes = 0x01;
                    //entry.FileName = directories[current];
                    entry.FirstCluster = free;

                    WriteDirectoryEntryToDirectory(currentcluster, ref entry);

                    currentcluster = free;
                    current++;

                    if (current > directories.Length - 1)
                    {
                        return;
                    }
                }
                else
                {
                    currentcluster = nextcluster;
                }
            }
        }

        private static uint GetDirectoryFirstCluster(string directory)
        {
            string[] directories = directory.Split('/');

            uint currentcluster = 0;
            int current = 0;

            while (true)
            {
            StartLoop:
                ReadCluster(currentcluster);

                for (int i = 0; i < filesystemdefinition.ClusterSizeInBytes; i += 64)
                {
                    if ((cluster[i] & 0x3) == 1)
                    {
                        string str = ASCIIEncoding.ASCII.GetString(cluster, i + 32, 32);
                        str = str.TrimEnd('\0');

                        if (str == directories[current])
                        {
                            current++;

                            if (current > directories.Length - 1)
                            {
                                return BitConverter.ToUInt32(cluster, i + 1);
                            }

                            currentcluster = BitConverter.ToUInt32(cluster, i + 1);
                            goto StartLoop;
                        }
                    }
                }

                uint nextcluster = GetNextClusterInChain(currentcluster);

                if (nextcluster == EndOfClusterChain)
                    return uint.MaxValue;
                else
                    currentcluster = nextcluster;
            }
        }

        private static bool DirectoryExists(string directory)
        {
            string[] directories = directory.Split('/');

            uint currentcluster = 0;
            int current = 0;

            while (true)
            {
            StartLoop:
                ReadCluster(currentcluster);

                for (int i = 0; i < filesystemdefinition.ClusterSizeInBytes; i += 64)
                {
                    if ((cluster[i] & 0x3) == 1)
                    {
                        string str = ASCIIEncoding.ASCII.GetString(cluster, i + 32, 32);
                        str = str.TrimEnd('\0');

                        if (str == directories[current])
                        {
                            current++;

                            if (current > directories.Length - 1)
                            {
                                return true;
                            }

                            currentcluster = BitConverter.ToUInt32(cluster, i + 1);
                            goto StartLoop;
                        }
                    }
                }

                uint nextcluster = GetNextClusterInChain(currentcluster);

                if (nextcluster == EndOfClusterChain)
                    return false;
                else
                    currentcluster = nextcluster;
            }
        }

        private static void AddFile(string diskFileName, string fileName)
        {
            string[] path = fileName.Split('/');
            string directory = null;

            if (path.Length > 1)
                directory = fileName.Substring(0, fileName.LastIndexOf('/'));

            FileStream file = File.Open(diskFileName, FileMode.Open, FileAccess.Read);
            byte[] data = new byte[file.Length];
            file.Read(data, 0, data.Length);

            byte[] sector = new byte[filesystemdefinition.SectorSizeInBytes];
            byte[] cluster = new byte[filesystemdefinition.ClusterSizeInBytes];
            
            //Find free clusters for the file
            int remainder;
            int clustersneeded = Math.DivRem(data.Length, filesystemdefinition.ClusterSizeInBytes, out remainder);
            
            if (remainder > 0)
                clustersneeded++;

            uint[] clustersused = FindFreeClusters(clustersneeded);

            //Write the file data to the free clusters
            WriteData(data, clustersused);

            //Create cluster chain
            WriteClusterChain(clustersused);

            //Write the filename
            uint filenamecluster = FindFreeCluster();
            byte[] filenamedata = ASCIIEncoding.ASCII.GetBytes(fileName);
            WriteData(filenamedata, filenamecluster);

            WriteClusterChain(filenamecluster);

            //Create the directory entry
            DirectoryEntry entry = new DirectoryEntry();
            entry.Attributes = 0x03;
            entry.FirstCluster = clustersused[0];
            entry.FileSize = (uint)file.Length;
            entry.FilenameCluster = filenamecluster;
            //entry.FileName = path[path.Length - 1];

            //Write directory entry to root directory
            if (path.Length == 1)
            {
                WriteDirectoryEntryToDirectory(0, ref entry);
            }
            else
            {
                uint firstcluster = GetDirectoryFirstCluster(directory);
                WriteDirectoryEntryToDirectory(firstcluster, ref entry);
            }

            //Close the file
            file.Close();
        }
    }
}