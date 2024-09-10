vfspos GetFileSize(const char* fn)
{
#ifdef VFS_LARGEFILE_SUPPORT
# ifdef _MSC_VER
    struct _stat64 st;
    if(_stat64(fn, &st))
        return 0;
    return st.st_size;
# else // _MSC_VER
    struct stat64 st;
    if(stat64(fn, &st))
        return 0;
    return st.st_size;
# endif
#else // VFS_LARGEFILE_SUPPORT
    struct stat st;
    if(stat(fn, &st))
        return 0;
    return st.st_size;
#endif
}