int File_RemoveW(
    _In_z_ const wchar_t* path)
{
#if defined(_MSC_VER)
    return _wunlink(path) == 0 ? 0 : -1;
#else
    char *filePath;
    int result;

    if( !UCS2ToAscii( path, &filePath) )
        return -1;

    result = unlink(filePath) == 0 ? 0 : -1;
    PAL_Free(filePath);
    return result;
#endif    
}