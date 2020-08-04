using System;
using System.IO;

namespace ImageWriter
{
    public class FileSystemDefinition
    {
        public const uint CatEntrySizeInBytes = sizeof(uint);

        readonly private uint sectorSizeInytes;
        readonly private uint clusterSizeInSectors;
        readonly private uint numberOfCatEntries;

        public FileSystemDefinition(uint sectorSizeInytes, uint clusterSizeInSectors, uint numberOfCatEntries)
        {
            this.sectorSizeInytes = sectorSizeInytes;
            this.clusterSizeInSectors = clusterSizeInSectors;
            this.numberOfCatEntries = numberOfCatEntries;
        }

        public byte[] GetBytes()
        {
            using (var data = new MemoryStream())
            using (var binaryWriter = new BinaryWriter(data))
            {
                data.SetLength(SectorSizeInBytes);
                data.Position = 0;

                binaryWriter.Write(SectorSizeInBytes);
                binaryWriter.Write(ClusterSizeInBytes);
                binaryWriter.Write(ClusterSizeInSectors);
                binaryWriter.Write(SectorCount);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(ClusterCount);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(CatSizeInExactBytes);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(CatSizeInBytes);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(CatSizeInSectors);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(DataAreaOffsetInBytes);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(DataAreaOffsetInSectors);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(DataAreaSizeInBytes);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(DataAreaSizeInSectors);
                binaryWriter.Write((uint)0);

                return data.ToArray();
            }
        }

        public uint SectorSizeInBytes
        {
            get
            {
                return sectorSizeInytes;
            }
        }

        public uint ClusterSizeInSectors
        {
            get
            {
                return clusterSizeInSectors;
            }
        }

        public uint NumberOfCatEntries
        {
            get
            {
                return numberOfCatEntries;
            }
        }

        public uint ClusterSizeInBytes
        {
            get
            {
                return ClusterSizeInSectors * SectorSizeInBytes;
            }
        }

        public uint SectorCount
        {
            get
            {
                return 2 + CatSizeInSectors + (ClusterSizeInSectors * NumberOfCatEntries);
            }
        }

        public uint ClusterCount
        {
            get
            {
                return NumberOfCatEntries;
            }
        }

        public uint CatSizeInExactBytes
        {
            get
            {
                return NumberOfCatEntries * CatEntrySizeInBytes;
            }
        }

        public uint CatSizeInBytes
        {
            get
            {
                return CatSizeInSectors * SectorSizeInBytes;
            }
        }

        public uint CatSizeInSectors
        {
            get
            {
                return (uint)Math.Ceiling((decimal)CatSizeInExactBytes / (decimal)SectorSizeInBytes);
            }
        }

        public uint DataAreaOffsetInBytes
        {
            get
            {
                return DataAreaOffsetInSectors * SectorSizeInBytes;
            }
        }

        public uint DataAreaOffsetInSectors
        {
            get
            {
                return 2 + CatSizeInSectors;
            }
        }

        public uint DataAreaSizeInBytes
        {
            get
            {
                return NumberOfCatEntries * ClusterSizeInBytes;
            }
        }

        public uint DataAreaSizeInSectors
        {
            get
            {
                return NumberOfCatEntries * ClusterSizeInSectors;
            }
        }
    }
}