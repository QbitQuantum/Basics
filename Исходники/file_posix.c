static BD_FILE_H *file_open_linux(const char* filename, const char *mode)
{
    FILE *fp = NULL;
    BD_FILE_H *file = malloc(sizeof(BD_FILE_H));

    BD_DEBUG(DBG_FILE, "Opening LINUX file %s... (%p)\n", filename, (void*)file);
    file->close = file_close_linux;
    file->seek = file_seek_linux;
    file->read = file_read_linux;
    file->write = file_write_linux;
    file->tell = file_tell_linux;
    file->eof = file_eof_linux;

#ifdef WIN32
    wchar_t wfilename[MAX_PATH], wmode[8];
    if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, filename, -1, wfilename, MAX_PATH) &&
        MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, mode, -1, wmode, 8) &&
        (fp = _wfopen(wfilename, wmode))) {
#else
    if ((fp = fopen(filename, mode))) {
#endif
        file->internal = fp;

        return file;
    }

    BD_DEBUG(DBG_FILE, "Error opening file! (%p)\n", (void*)file);

    X_FREE(file);

    return NULL;
}

BD_FILE_H* (*file_open)(const char* filename, const char *mode) = file_open_linux;

BD_FILE_OPEN file_open_default(void)
{
    return file_open_linux;
}