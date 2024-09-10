static int64_t _file_tell(BD_FILE_H *file)
{
#if defined(__MINGW32__)
    return ftello64((FILE *)file->internal);
#else
    return _ftelli64((FILE *)file->internal);
#endif
}