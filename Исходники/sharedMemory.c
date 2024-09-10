hSharedMemory* OpenSharedMemory(char* MapFileName, char* mutex, int size)
{
    hSharedMemory* handle = malloc(sizeof(hSharedMemory));
    handle->hFile = NULL;
    handle->hFileView = NULL;
    handle->hFileMutex = NULL;

    // Try to open File Mapping...
    handle->hFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, MapFileName);

    // ... ok it might not exist, so create try to create it...
    if (handle->hFile == NULL)
        handle->hFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, size & 0xFFFF0000, size & 0xFFFF, MapFileName);

    // ... if create fails we are lost...
    if (handle->hFile == 0)
    {
        CloseSharedMemory(handle);
        return NULL;
    }

    handle->hFileView = MapViewOfFile(handle->hFile, FILE_MAP_ALL_ACCESS, 0, 0, size);

    if (handle->hFileView == NULL)
    {
        CloseSharedMemory(handle);
        return NULL;
    }

    handle->hFileMutex = CreateMutexA(NULL, FALSE, mutex);

    if (handle->hFileMutex == NULL)
    {
        CloseSharedMemory(handle);
        return NULL;
    }

    return handle;
}