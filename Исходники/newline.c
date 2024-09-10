static FILE* open_file(const arg_char* name) {
#ifdef _WIN32
    // Open the file allowing shared read, but not shared write
    int fd;
    _wsopen_s(
        &fd, name, _O_RDWR | _O_BINARY | _O_NOINHERIT, _SH_DENYWR,
        _S_IREAD | _S_IWRITE
    );
    if(fd == -1) {
        return NULL;
    }
    FILE* file = _fdopen(fd, "r+b");
    if(file == NULL) {
        _close(fd);
        return NULL;
    }
    setvbuf(file, NULL, _IOFBF, FileBufferLen);
    return file;
#else
    FILE* file = fopen(name, "r+b");
    if(file != NULL) {
        setvbuf(file, NULL, _IOFBF, FileBufferLen);
    }
    return file;
#endif // _WIN32
}