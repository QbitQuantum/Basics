HANDLE apiCreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, LPDWORD lpThreadId, LPCSTR asThreadNameFormat /*= NULL*/, int anFormatArg /*= 0*/)
{
    HANDLE hThread = NULL;
    ConEmuThreadStartArg* args = new ConEmuThreadStartArg(lpStartAddress, lpParameter, GetCurrentThreadId());
    if (!args)
    {
        // Not enough memory
        return NULL;
    }

    // Set user-friendly thread name for VisualStudio debugger
    if (asThreadNameFormat && *asThreadNameFormat)
    {
        if (strchr(asThreadNameFormat, '%') != NULL)
        {
            INT_PTR cchMax = strlen(asThreadNameFormat) + 64;
            char* pszNewName = new char[cchMax];
            if (pszNewName)
            {
                _wsprintfA(pszNewName, SKIPLEN(cchMax) asThreadNameFormat, anFormatArg);
                _ASSERTE(strlen(pszNewName) < THREAD_MAX_NAME_LEN);
                lstrcpynA(args->sName, pszNewName, countof(args->sName));
                delete[] pszNewName;
            }
        }

        if (args->sName[0] == 0)
        {
            _ASSERTE(strlen(asThreadNameFormat) < THREAD_MAX_NAME_LEN);
            lstrcpynA(args->sName, asThreadNameFormat, countof(args->sName));
        }
    }

    // Start the thread
    hThread = ::CreateThread(NULL, 0, apiThreadHelper, args, CREATE_SUSPENDED, lpThreadId);
    DWORD nLastError = GetLastError();
    if (hThread)
    {
        args->hThread = hThread;
        ResumeThread(hThread);
    }
    else
    {
        delete args;
    }

    // Done
    SetLastError(nLastError);
    return hThread;
}