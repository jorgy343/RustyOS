using System;

namespace ImageWriter
{
    [Flags]
    public enum DirectoryEntryAttributes : byte
    {
        DoesExist = 1,
        IsFile = 2,
        IsHidden = 4,
        IsReadOnly = 8,
        IsSystemSpecific = 16
    }
}