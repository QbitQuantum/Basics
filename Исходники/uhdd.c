int uGetFileSize(UFile fd, __int64 * file_size, sys_call_error_fun fun)
{
#ifdef _WIN32
    LARGE_INTEGER size;
    BOOL res = GetFileSizeEx(fd, &size);
    if (res == 0)
        sys_call_error("GetFileSizeEx");
    else
        *file_size = size.QuadPart;
    return res;
#else
    struct stat64 buf;
    if (fstat64(fd, &buf) == -1)
    {
        sys_call_error("fstat64");
        return 0;
    }
    *file_size = buf.st_size;
    return 1;
#endif
}