using System;

namespace ImageWriter
{
    public class Cat
    {
        readonly private uint numberOfCatEntries;
        readonly private uint clusterSizeInBytes;
        readonly private CatEntry[] entries;

        public Cat(uint numberOfCatEntries, uint clusterSizeInBytes)
        {
            if (numberOfCatEntries < 1)
                throw new ArgumentOutOfRangeException("numberOfCatEntries", "numberOfCatEntries must be greater than or equal to 1.");

            this.numberOfCatEntries = numberOfCatEntries;
            this.clusterSizeInBytes = clusterSizeInBytes;
            this.entries = new CatEntry[numberOfCatEntries];

            entries[0] = new CatEntry(0, CatEntryType.DirectoryEntryData, clusterSizeInBytes);

            for (uint i = 1; i < entries.Length; ++i)
                entries[i] = new CatEntry(i, CatEntryType.Unused, clusterSizeInBytes);
        }
    }
}