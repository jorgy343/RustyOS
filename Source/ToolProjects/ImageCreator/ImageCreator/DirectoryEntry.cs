using System;
using System.Collections.Generic;
using System.IO;
using System.Text;


namespace ImageCreator
{
    public struct DirectoryEntry
    {
        public byte Attributes;
        public uint FirstCluster;
        public uint FileSize;
        public uint FilenameCluster;
        public DateTime CreationTime, ModifiedTime, AccessedTime;


        public byte[] ToBytes()
        {
            MemoryStream memory = new MemoryStream(64);
            BinaryWriter writer = new BinaryWriter(memory);

            //Offset 0
            writer.Write(Attributes);

            //Offset 1-7
            WriteSevenZeroBytes(writer);

            //Offset 8-11
            writer.Write(FirstCluster);

            //Offset 12-15
            WriteFourZeroBytes(writer);

            //Offset 16-19
            writer.Write(FileSize);

            //Offset 20-23
            WriteFourZeroBytes(writer);

            //Offset 24-27
            writer.Write(FilenameCluster);

            //Offset 28-31
            WriteFourZeroBytes(writer);

            //Offset 32-39
            writer.Write(CreationTime.ToBinary());

            //Offset 40-47
            writer.Write(ModifiedTime.ToBinary());

            //Offset 48-55
            writer.Write(AccessedTime.ToBinary());

            //Offset 56-63
            WriteEightZeroBytes(writer);


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

        private void WriteSevenZeroBytes(BinaryWriter writer)
        {
            writer.Write((byte)0);
            writer.Write((byte)0);
            writer.Write((byte)0);
            writer.Write((byte)0);

            writer.Write((byte)0);
            writer.Write((byte)0);
            writer.Write((byte)0);
        }

        private void WriteEightZeroBytes(BinaryWriter writer)
        {
            writer.Write((byte)0);
            writer.Write((byte)0);
            writer.Write((byte)0);
            writer.Write((byte)0);

            writer.Write((byte)0);
            writer.Write((byte)0);
            writer.Write((byte)0);
            writer.Write((byte)0);
        }
    }
}