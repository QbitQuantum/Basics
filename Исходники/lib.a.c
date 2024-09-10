VOID InitLibrary(BOOLEAN _LibraryMode, ULONG _VirtualFileSize, ULONG _PhysicalFileSize, int _MaxSnapshotCount)
{
    LibraryMode = _LibraryMode;
    VirtualFileSize = _VirtualFileSize;
    PhysicalFileSize = _PhysicalFileSize;
    
    TableStorage = CreatePTableArray(_MaxSnapshotCount + 1);
    CurrentTable = CreateTable();
    ReadonlyNodes = CreateTable();
    
    MapInterval(0, 0, VirtualFileSize);
    SnapshotZeroSave(0);
}