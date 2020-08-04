using System;
using System.Collections.Generic;
using System.IO;
using System.Text;


namespace ImageCreator
{
    public class FileSystemDefinition
    {
        public int SectorSizeInBytes = 512;
        public int ClusterSizeInBytes = 4096;
        public int ClusterSizeInSectors;
        public uint CatSizeInBytes;
        public uint CatSizeInSectors;
        public uint DataOffsetInBytes;
        public uint DataOffsetInSectors;
        public uint SectorCount = 2880;
        public uint ClusterCount;


        public void CalculateParameters()
        {
            //Cluster size >= sector size
            ClusterSizeInSectors = ClusterSizeInBytes / SectorSizeInBytes;

            //This is a very rough (and probably wrong) way to figure out about
            //how many clusters can fit inside the file system given the specified
            //length (in sectors).
            ClusterCount = SectorCount / (uint)ClusterSizeInSectors;

            //The actual CAT is the number of clusters times the size of each
            //CAT entry. Each CAT entry is a uint (4 bytes).
            CatSizeInBytes = ClusterCount * 4;

            //The CAT size in sectors. The specs say that the CAT must be padded
            //by zero's if the end is not naturally aligned to a sector boundary.
            long remainder;
            CatSizeInSectors = (uint)Math.DivRem((long)CatSizeInBytes, (long)SectorSizeInBytes, out remainder);
            if (remainder > 0)
                CatSizeInSectors++;

            //The offset to the data area in sectors is obtained using the
            //following formula:
            //DataOffsetInSectors = (1 + 3) + CatSizeInSectors
            DataOffsetInSectors = (1 + 3) + CatSizeInSectors;

            //The offset to the data area in bytes is obtained simply by
            //multiplying the offset in sectors by the sector size in bytes
            DataOffsetInBytes = DataOffsetInSectors * (uint)SectorSizeInBytes;
        }

        public byte[] ToBytes()
        {
            MemoryStream memory = new MemoryStream(3 * SectorSizeInBytes);
            BinaryWriter writer = new BinaryWriter(memory);

            //Offset 0-3
            writer.Write(SectorSizeInBytes);

            //Offset 4-7
            writer.Write(ClusterSizeInBytes);

            //Offset 8-11
            writer.Write(ClusterSizeInSectors);

            //Offset 12-15
            writer.Write(CatSizeInBytes);

            //Offset 16-19
            WriteFourZeroBytes(writer);

            //Offset 20-23
            writer.Write(CatSizeInSectors);

            //Offset 24-27
            WriteFourZeroBytes(writer);

            //Offset 28-31
            writer.Write(DataOffsetInBytes);

            //Offset 32-35
            WriteFourZeroBytes(writer);

            //Offset 36-39
            writer.Write(DataOffsetInSectors);

            //Offset 40-43
            WriteFourZeroBytes(writer);

            //Offset 44-47
            writer.Write(SectorCount);

            //Offset 48-51
            WriteFourZeroBytes(writer);

            //Offset 52-55
            writer.Write(ClusterCount);

            //Offset 56-59
            WriteFourZeroBytes(writer);


            //Fill rest with zeros
            while (memory.Position < 3 * SectorSizeInBytes)
            {
                writer.Write((byte)0);
            }


            writer.Flush();
            byte[] data = memory.ToArray();
            writer.Close();
            return data;
        }

        private void WriteFourZeroBytes(BinaryWriter writer)
        {
            writer.Write((byte)0);
            writer.Write((byte)0);
            writer.Write((byte)0);
            writer.Write((byte)0);
        }
    }
}