void
__funlockfile (FILE *stream)
{
    HANDLE hf;
    int fd;
    LARGE_INTEGER li;

    fd = _fileno (stream);
    hf = (HANDLE) _get_osfhandle (fd);
    li.QuadPart = _filelengthi64 (fd);
    UnlockFile (hf, 0, 0, li.LowPart, li.HighPart);
}