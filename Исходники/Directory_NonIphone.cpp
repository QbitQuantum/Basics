LLBC_String LLBC_Directory::HomeDir()
{
#if LLBC_TARGET_PLATFORM_WIN32
    size_t requiredSize = 0;
    if (getenv_s(&requiredSize, NULL, 0, "HOMEPATH") != 0)
    {
        LLBC_SetLastError(LLBC_ERROR_CLIB);
        return LLBC_String();
    }
    else if (requiredSize == 0)
    {
        LLBC_SetLastError(LLBC_ERROR_NOT_FOUND);
        return LLBC_String();
    }

    char *envVal = LLBC_Malloc(char, requiredSize);
    if (getenv_s(&requiredSize, envVal, requiredSize, "HOMEPATH") != 0)
    {
        LLBC_Free(envVal);
        LLBC_SetLastError(LLBC_ERROR_CLIB);
        return LLBC_String();
    }

    LLBC_String path(envVal);
    LLBC_Free(envVal);
#else // Non-Win32
    char *envVal = getenv("HOME");
    if (!envVal)
    {
        LLBC_SetLastError(LLBC_ERROR_NOT_FOUND);
        return "";
    }
    const LLBC_String path(envVal);
#endif // Win32

#if LLBC_TARGET_PLATFORM_WIN32
    const size_t pathLen = path.length();
    if (path[pathLen - 1] == LLBC_SLASH_A ||
        path[pathLen - 1] == LLBC_BACKLASH_A)
    {
        if (pathLen == 3 &&
            LLBC_String::isalpha(path[0]) &&
            path[1] == ':')
            return path;
        else
            return path.substr(0, pathLen - 1);
    }
    else
    {
        return path;
    }
#else // Non-Win32
    const size_t pathLen = path.length();
    if (path[pathLen - 1] == LLBC_SLASH_A)
    {
        if (pathLen == 1)
            return path;
        else
            return path.substr(0, path.length() -1);
    }
    else
    {
        return path;
    }
#endif // Win32
}