PHP_WIN32_IPC_API key_t
ftok(const char *pathname, int proj_id)
{
    HANDLE fh;
    struct stat st;
    BY_HANDLE_FILE_INFORMATION bhfi;
    key_t ret;

    if (stat(pathname, &st) < 0) {
        return (key_t)-1;
    }

    if ((fh = CreateFile(pathname, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0)) == INVALID_HANDLE_VALUE) {
        return (key_t)-1;
    }

    if (!GetFileInformationByHandle(fh, &bhfi)) {
        CloseHandle(fh);
        return (key_t)-1;
    }

    ret = (key_t) ((proj_id & 0xff) << 24 | (st.st_dev & 0xff) << 16 | ((bhfi.nFileIndexLow | (__int64)bhfi.nFileIndexHigh << 32) & 0xffff));

    CloseHandle(fh);

    return ret;
}