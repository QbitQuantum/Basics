int main(int argc, const char *argv[])
{
    if (argc <= 1) {
        return -1;
    }
    char dsk[MAX_PATH], dir[MAX_PATH];
    _splitpath(argv[1], dsk, dir, NULL, NULL);

    FILE *f = fopen(argv[1], "rt");
    if (!f) {
        return -2;
    }

    DWORD err = 0;
    ULONG_PTR newImageBase = 0x30000000;
    char file[MAX_PATH];
    while (fgets(file, MAX_PATH, f)) {
        if (char *eoln = strchr(file, '\n')) {
            *eoln = '\0';
        }
        ULONG_PTR oldImageSize = 0, oldImageBase = 0, newImageSize = 0;
        char flnm[MAX_PATH];
        _makepath(flnm, dsk, dir, file, NULL);
        BOOL ret = ReBaseImage(flnm, NULL, TRUE, FALSE, FALSE, 0, &oldImageSize, &oldImageBase, &newImageSize, &newImageBase, 0);
        err = GetLastError();
        if (err) {
            printf("rebase %s: error %i\n", file, err);
        } else {
            printf("rebase %s: %08x -> %08x, size %i\n", file, oldImageBase, newImageBase, newImageSize);
        }
        newImageBase = ((newImageBase + newImageSize)&~65535) + 65536;
    }

    fclose(f);
    return err;
}