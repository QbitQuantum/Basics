void MappedMemory::release(void)
{
    if(map) {
        if(use_mapping) {
            VirtualUnlock(map, size);
            UnmapViewOfFile(fd);
            CloseHandle(fd);
            map = NULL;
            fd = INVALID_HANDLE_VALUE;
        }
        else {
            free(map);
            map = NULL;
        }
    }
    if(erase) {
        remove(idname);
        erase = false;
    }
}