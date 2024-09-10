static int _file_load(const char *file, void **data, u32 * len)
{
    HANDLE h, fmo;
    LARGE_INTEGER size;
    void *buf;

    h = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (h == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "ERROR: failed to open file %s\n", file);
        return -1;
    }

    // figure out how big the file is.
    if (GetFileSizeEx(h, &size) == 0) {
        fprintf(stderr, "ERROR: failed to get size of file %s\n", file);
        return -1;
    }

    fmo = CreateFileMapping(h, NULL, PAGE_READONLY, size.u.HighPart, size.u.LowPart, NULL);
    if (fmo == NULL) {
        fprintf(stderr, "ERROR: failed to create file mapping for file %s: %d\n", file, GetLastError());
        return -1;
    }

    buf = MapViewOfFile(fmo, FILE_MAP_READ, 0, 0, size.u.LowPart);
    if (buf == NULL) {
        fprintf(stderr, "ERROR: failed to create a file view for file %s: %d\n", file, GetLastError());
        return -1;
    }

    printf("file %s (size=%ld) mapped at %p\n", file,
           size.u.LowPart, buf);

    *data = buf;
    *len = size.u.LowPart;

    return 0;
}