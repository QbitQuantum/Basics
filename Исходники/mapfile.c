void*
mapfile_map(MapFile* handle,
            size_t offset,
            size_t size,
            int prot,
            void** mapped_offset,
            size_t* mapped_size)
{
    void* mapped_at = NULL;
    size_t align_mask;
    size_t map_offset;
    size_t map_size;

  /* Get the mask for mapping offset alignment. */
#ifdef  WIN32
    DWORD win32_prot;
    DWORD win32_map;
    HANDLE map_handle;
    LARGE_INTEGER converter;
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    align_mask = sys_info.dwAllocationGranularity - 1;
#else   // WIN32
    align_mask = getpagesize() - 1;
#endif  // WIN32

    /* Adjust mapping offset and mapping size accordingly to
     * the mapping alignment requirements. */
    map_offset = offset & ~align_mask;
    map_size = (size_t)(offset - map_offset + size);

    /* Make sure mapping size doesn't exceed 4G. */
    if (map_size < size) {
        errno = EFBIG;
        return NULL;
    }

    /* Map the section. */
#ifdef  WIN32
    /* Convert to Win32 page protection and mapping type. */
    win32_prot = PAGE_READONLY;
    win32_map = FILE_MAP_READ;
    if (prot != PROT_NONE) {
        if ((prot & (PROT_WRITE | PROT_EXEC)) == 0) {
            win32_prot = PAGE_READONLY;
            win32_map = FILE_MAP_READ;
        } else if ((prot & (PROT_WRITE | PROT_EXEC)) ==
                   (PROT_WRITE | PROT_EXEC)) {
            win32_prot = PAGE_EXECUTE_READWRITE;
            win32_map = FILE_MAP_WRITE;
        } else if ((prot & PROT_WRITE) == PROT_WRITE) {
            win32_prot = PAGE_READWRITE;
            win32_map = FILE_MAP_WRITE;
        } else if ((prot & PROT_EXEC) == PROT_EXEC) {
            win32_prot = PAGE_EXECUTE_READ;
            win32_map = FILE_MAP_READ;
        }
    }

    converter.QuadPart = map_offset + map_size;
    map_handle = CreateFileMapping(handle, NULL, win32_prot,
                                   converter.HighPart, converter.LowPart, NULL);
    if (map_handle != NULL) {
        converter.QuadPart = map_offset;
        mapped_at = MapViewOfFile(map_handle, win32_map, converter.HighPart,
                                  converter.LowPart, map_size);
        /* Memory mapping (if successful) will hold extra references to the
        * mapping, so we can close it right after we mapped file view. */
        CloseHandle(map_handle);
    }
    if (mapped_at == NULL) {
        errno = GetLastError();
        return NULL;
    }
#else   // WIN32
    mapped_at =
        mmap(0, map_size, PROT_READ, MAP_SHARED, (int)handle, map_offset);
    if (mapped_at == MAP_FAILED) {
        return NULL;
    }
#endif  // WIN32

    *mapped_offset = (char*)mapped_at + (offset - map_offset);
    *mapped_size = size;

    return mapped_at;
}