bool plFileUtils::RemoveFile(const wchar_t* filename, bool delReadOnly)
{
#ifdef HS_BUILD_FOR_WIN32
    if (delReadOnly)
        _wchmod(filename, S_IWRITE);
    return (_wunlink(filename) == 0);
#elif HS_BUILD_FOR_UNIX
    const char* cfilename = hsWStringToString(filename);
    bool ret = RemoveFile(cfilename, delReadOnly);
    delete[] cfilename; /* Free the string */

    return ret;
#endif
}