static NTSTATUS Create(FSP_FILE_SYSTEM *FileSystem,
    FSP_FSCTL_TRANSACT_REQ *Request,
    PWSTR FileName, BOOLEAN CaseSensitive, UINT32 CreateOptions,
    UINT32 FileAttributes, PSECURITY_DESCRIPTOR SecurityDescriptor, UINT64 AllocationSize,
    PVOID *PFileNode, FSP_FSCTL_FILE_INFO *FileInfo)
{
    MEMFS *Memfs = (MEMFS *)FileSystem->UserContext;
    MEMFS_FILE_NODE *FileNode;
    NTSTATUS Result;
    BOOLEAN Inserted;

    if (CreateOptions & FILE_DIRECTORY_FILE)
        AllocationSize = 0;

    FileNode = MemfsFileNodeMapGet(Memfs->FileNodeMap, FileName);
    if (0 != FileNode)
        return STATUS_OBJECT_NAME_COLLISION;

    if (!MemfsFileNodeMapGetParent(Memfs->FileNodeMap, FileName, &Result))
        return Result;

    if (MemfsFileNodeMapCount(Memfs->FileNodeMap) >= Memfs->MaxFileNodes)
        return STATUS_CANNOT_MAKE;

    if (AllocationSize > Memfs->MaxFileSize)
        return STATUS_DISK_FULL;

    Result = MemfsFileNodeCreate(FileName, &FileNode);
    if (!NT_SUCCESS(Result))
        return Result;

    FileNode->FileInfo.FileAttributes = (FileAttributes & FILE_ATTRIBUTE_DIRECTORY) ?
        FileAttributes : FileAttributes | FILE_ATTRIBUTE_ARCHIVE;

    if (0 != SecurityDescriptor)
    {
        FileNode->FileSecuritySize = GetSecurityDescriptorLength(SecurityDescriptor);
        FileNode->FileSecurity = (PSECURITY_DESCRIPTOR)malloc(FileNode->FileSecuritySize);
        if (0 == FileNode->FileSecurity)
        {
            MemfsFileNodeDelete(FileNode);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        memcpy(FileNode->FileSecurity, SecurityDescriptor, FileNode->FileSecuritySize);
    }

    FileNode->FileInfo.AllocationSize = AllocationSize;
    if (0 != FileNode->FileInfo.AllocationSize)
    {
        FileNode->FileData = malloc((size_t)FileNode->FileInfo.AllocationSize);
        if (0 == FileNode->FileData)
        {
            MemfsFileNodeDelete(FileNode);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
    }

    Result = MemfsFileNodeMapInsert(Memfs->FileNodeMap, FileNode, &Inserted);
    if (!NT_SUCCESS(Result) || !Inserted)
    {
        MemfsFileNodeDelete(FileNode);
        if (NT_SUCCESS(Result))
            Result = STATUS_OBJECT_NAME_COLLISION; /* should not happen! */
        return Result;
    }

    FileNode->RefCount++;
    *PFileNode = FileNode;
    *FileInfo = FileNode->FileInfo;

    return STATUS_SUCCESS;
}