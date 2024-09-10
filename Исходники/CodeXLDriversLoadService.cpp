void main(int argc, char* argv[])
{
    // error message
    wchar_t pTemp[121];
    unsigned int errStrSize = 120;

    // initialize global critical section
    ::InitializeCriticalSection(&gCS);

    // initialize variables for .exe, .ini, and .log file names
    wchar_t pModuleFile[nBufferSize + 1];
    DWORD dwSize = GetModuleFileName(nullptr, (LPTSTR)pModuleFile, nBufferSize);
    pModuleFile[dwSize] = 0;

    if (dwSize > 4 && pModuleFile[dwSize - 4] == '.')
    {
        swprintf(pExeFile, nBufferSize, L"%s", pModuleFile);
        pModuleFile[dwSize - 4] = 0;
        swprintf(pLogFile, nBufferSize, L"%s.log", pModuleFile);
    }
    else
    {
        printf("Invalid module file name: %ws\r\n", pModuleFile);
        return;
    }

    WriteLog(pExeFile);
    WriteLog(pLogFile);
    wcscpy_s(pServiceName, 500, L"CodeXLDriversLoadService");
    WriteLog(pServiceName);

    // uninstall service if switch is "-u"
    if (argc == 2 && _stricmp("-uninstall", argv[1]) == 0)
    {
        UnInstall(pServiceName);
    }
    // install service if switch is "-i"
    else if (argc == 2 && _stricmp("-install", argv[1]) == 0)
    {
        Install(pExeFile, pServiceName);
    }
    // stop a service with given name
    else if (argc == 2 && _stricmp("-stop", argv[1]) == 0)
    {
        if (StopService(pServiceName))
        {
            swprintf(pTemp, errStrSize, L"Stopped service %s", pServiceName);
            WriteLog(pTemp);
        }
        else
        {
            swprintf(pTemp, errStrSize, L"Failed to stop service %s", pServiceName);
            WriteLog(pTemp);
        }
    }
    // run a service with given name
    else if (argc == 2 && _stricmp("-start", argv[1]) == 0)
    {
        WriteLog(L"StartService");

        if (StartService(pServiceName, 0, nullptr))
        {
            swprintf(pTemp, errStrSize, L"Ran service %s", pServiceName);
            WriteLog(pTemp);
        }
        else
        {
            swprintf(pTemp, errStrSize, L"Failed to run service %s", pServiceName);
            WriteLog(pTemp);
        }
    }
    // assume user is starting this service
    else
    {
        // start a worker thread to load driver
        if (_beginthread(WorkerProc, 0, nullptr) == -1)
        {
            WriteErrorLog(L"_beginthread failed");
        }

        // pass dispatch table to service controller
        if (!StartServiceCtrlDispatcher(DispatchTable))
        {
            WriteErrorLog(L"StartServiceCtrlDispatcher failed");
        }

        // you don't get here unless the service is shutdown
    }

    ::DeleteCriticalSection(&gCS);
}