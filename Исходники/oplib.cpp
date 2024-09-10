bool opLoadLib(LibHandle* handle, const char* libpath)
{
    if (handle == nullptr || libpath == nullptr || strlen(libpath) == 0)
    {
        LOG_ERROR(opLib) << "opLoadLib: No library specified";
        return false;
    }

#ifdef _MSC_VER
    const size_t size = strlen(libpath) + 1;
    std::wstring path(size, L'#');
    size_t convnum = 0;

    mbstowcs_s(&convnum, &path[0], size, libpath, _TRUNCATE);

    *handle = LoadLibrary(path.c_str());

    if (*handle == nullptr)
    {
        LPVOID lpMsgBuf;
        LPVOID lpDisplayBuf;
        DWORD dwErr = GetLastError();
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dwErr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL);

        lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
            (lstrlen((LPCTSTR)lpMsgBuf) + 40) * sizeof(TCHAR));
        StringCchPrintf((LPTSTR)lpDisplayBuf,
            LocalSize(lpDisplayBuf) / sizeof(TCHAR),
            TEXT("error %d: %s"),
            dwErr, lpMsgBuf);

        std::string errMsg = MBFromW((LPCTSTR)lpDisplayBuf, CP_ACP);

        LOG_ERROR(opLib) << "opLoadLib('" << libpath << "') " << errMsg;
        LocalFree(lpMsgBuf);
        LocalFree(lpDisplayBuf);
        return false;
    }
#else
    *handle = dlopen(libpath, RTLD_NOW);

    if (*handle == nullptr)
    {
        LOG_ERROR(opLib) << "dlopen('" << libpath << "') failed: " << dlerror();
        return false;
    }
#endif

    return true;
}