int
map_file(const char *filename, void *addr, int image)
{
    HANDLE map;
    PBYTE view;
    /* Must specify FILE_SHARE_READ to open if -persist_lock_file is in use */
    HANDLE file = CreateFileA(filename, GENERIC_READ | (image ? FILE_EXECUTE : 0),
                              FILE_SHARE_READ, NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == NULL) {
        int err = GetLastError();
        fprintf(stderr, "Error %d opening \"%s\"\n", err, filename);
        return 0;
    }
    /* For image, it fails w/ ACCESS_DENIED at the map stage if we ask for
     * more than PAGE_READONLY, and at the view stage if we ask for
     * anything more than FILE_MAP_READ.
     */
    map = CreateFileMapping(file, NULL,
                            PAGE_READONLY | (image ? SEC_IMAGE : 0), 
                            0, 0, NULL);
    if (map == NULL) {
        int err = GetLastError();
        CloseHandle(file);
        fprintf(stderr, "Error %d mapping \"%s\"\n", err, filename);
        return 0;
    }
    view = MapViewOfFileEx(map, FILE_MAP_READ, 0, 0, 0, addr);
    if (view == NULL) {
        int err = GetLastError();
        CloseHandle(map);
        CloseHandle(file);
        fprintf(stderr, "Error %d mapping view of \"%s\"\n", err, filename);
        return 0;
    }
    return 1;
}