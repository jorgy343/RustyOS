using System;
using System.IO;

namespace ImageWriter
{
    public class DirectoryEntry
    {
        public const int SizeOfDirectoryEntry = 64;

        public byte[] GetBytes()
        {
            using (var data = new MemoryStream())
            using (var binaryWriter = new BinaryWriter(data))
            {
                data.SetLength(SizeOfDirectoryEntry);
                data.Position = 0;

                binaryWriter.Write((byte)Attributes);
                binaryWriter.Write((byte)0);
                binaryWriter.Write((byte)0);
                binaryWriter.Write((byte)0);
                binaryWriter.Write((byte)0);
                binaryWriter.Write((byte)0);
                binaryWriter.Write((byte)0);
                binaryWriter.Write((byte)0);
                binaryWriter.Write(FirstCluster);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(FileSize);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(FileNameCluster);
                binaryWriter.Write((uint)0);
                binaryWriter.Write(CreationTime.Ticks);
                binaryWriter.Write(ModifiedTime.Ticks);
                binaryWriter.Write(AccessedTime.Ticks);
                binaryWriter.Write((uint)0);

                return data.ToArray();
            }
        }

        public DirectoryEntryAttributes Attributes { get; set; }
        public uint FirstCluster { get; set; }
        public uint FileSize { get; set; }
        public uint FileNameCluster { get; set; }
        public DateTime CreationTime { get; set; }
        public DateTime ModifiedTime { get; set; }
        public DateTime AccessedTime { get; set; }
    }
}