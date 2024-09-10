/* creates a temporary file with the data in it.  If *filename_out gets set,
 * the caller should try to unlink it. */
int
regress_make_tmpfile(const void *data, size_t datalen, char **filename_out)
{
#ifndef _WIN32
    char tmpfilename[32];
    int fd;
    *filename_out = NULL;
    strcpy(tmpfilename, "/tmp/eventtmp.XXXXXX");
#ifdef EVENT__HAVE_UMASK
    umask(0077);
#endif
    fd = mkstemp(tmpfilename);
    if (fd == -1)
        return (-1);
    if (write(fd, data, datalen) != (int)datalen) {
        close(fd);
        return (-1);
    }
    lseek(fd, 0, SEEK_SET);
    /* remove it from the file system */
    unlink(tmpfilename);
    return (fd);
#else
    /* XXXX actually delete the file later */
    char tmpfilepath[MAX_PATH];
    char tmpfilename[MAX_PATH];
    DWORD r, written;
    int tries = 16;
    HANDLE h;
    r = GetTempPathA(MAX_PATH, tmpfilepath);
    if (r > MAX_PATH || r == 0)
        return (-1);
    for (; tries > 0; --tries) {
        r = GetTempFileNameA(tmpfilepath, "LIBEVENT", 0, tmpfilename);
        if (r == 0)
            return (-1);
        h = CreateFileA(tmpfilename, GENERIC_READ|GENERIC_WRITE,
                        0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (h != INVALID_HANDLE_VALUE)
            break;
    }
    if (tries == 0)
        return (-1);
    written = 0;
    *filename_out = strdup(tmpfilename);
    WriteFile(h, data, (DWORD)datalen, &written, NULL);
    /* Closing the fd returned by this function will indeed close h. */
    return _open_osfhandle((intptr_t)h,_O_RDONLY);
#endif
}