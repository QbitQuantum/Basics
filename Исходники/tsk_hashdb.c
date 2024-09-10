static FILE *
    hdb_open_file(TSK_TCHAR *file_path)
{
    FILE *file = NULL;

#ifdef TSK_WIN32
    int fd = 0;
    if (_wsopen_s(&fd, file_path, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) == 0) {
        file = _wfdopen(fd, L"rb");
    }
#else
    file = fopen(file_path, "rb");
#endif

    return file;
}