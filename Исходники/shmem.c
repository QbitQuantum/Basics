void *open_shared_mem(LPCWSTR name, DWORD size, HANDLE *hmap)
{
    HANDLE map;
    void *ptr;

    map = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, name);
    if(map == NULL) {
        return NULL;
    }

    ptr = MapViewOfFile(map, FILE_MAP_ALL_ACCESS, 0, 0, size);

    if(ptr != NULL) {
        *hmap = map;
    }

    return ptr;
}