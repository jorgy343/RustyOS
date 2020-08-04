using System.IO;

namespace ImageWriter
{
    public class CatEntry
    {
        readonly private uint index;
        readonly private CatEntryType catEntryType;
        readonly private uint clusterSizeInBytes;
        readonly private byte[] fileData;
        readonly private DirectoryEntry[] directoryEntries;
        private string filename;

        public CatEntry(uint index, CatEntryType catEntryType, uint clusterSizeInBytes)
        {
            this.index = index;
            this.catEntryType = catEntryType;
            this.clusterSizeInBytes = clusterSizeInBytes;

            this.fileData = new byte[clusterSizeInBytes];
            this.directoryEntries = new DirectoryEntry[clusterSizeInBytes / DirectoryEntry.SizeOfDirectoryEntry];
        }

        public uint Index
        {
            get
            {
                return index;
            }
        }

        public CatEntryType CatEntryType
        {
            get
            {
                return catEntryType;
            }
        }

        public uint ClusterSizeInBytes
        {
            get
            {
                return clusterSizeInBytes;
            }
        }

        public byte[] FileData
        {
            get
            {
                return fileData;
            }
        }

        public DirectoryEntry[] DirectoryEntries
        {
            get
            {
                return directoryEntries;
            }
        }

        public string Filename
        {
            get
            {
                return filename;
            }
            set
            {
                filename = value;
            }
        }
    }
}