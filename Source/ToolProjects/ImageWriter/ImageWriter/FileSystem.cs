using System;
using System.Collections.Generic;

namespace ImageWriter
{
    public class FileSystem
    {
        readonly private byte[] bootSector;
        readonly private FileSystemDefinition fileSystemDefinition;
        readonly private uint[] cat;
        readonly private List<string> filesToAdd;

        public FileSystem(byte[] bootSector, FileSystemDefinition fileSystemDefinition)
        {
            if (bootSector == null)
                throw new ArgumentNullException("bootSector");

            if (fileSystemDefinition == null)
                throw new ArgumentNullException("fileSystemDefinition");

            if (bootSector.Length != fileSystemDefinition.SectorSizeInBytes)
                throw new ArgumentException("bootSector must have the same length as the sector size in bytes.", "bootSector");

            this.bootSector = bootSector;
            this.fileSystemDefinition = fileSystemDefinition;

            this.cat = new uint[fileSystemDefinition.NumberOfCatEntries];
            this.filesToAdd = new List<string>();
        }

        public byte[] BootSector
        {
            get
            {
                return bootSector;
            }
        }

        public FileSystemDefinition FileSystemDefinition
        {
            get
            {
                return fileSystemDefinition;
            }
        }

        public ICollection<string> FilesToAdd
        {
            get
            {
                return filesToAdd;
            }
        }
    }
}