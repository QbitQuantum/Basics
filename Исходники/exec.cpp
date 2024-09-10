int execute(const std::wstring& commandLine, const commandlineProcessor& options)
{
    wchar_t * environment = nullptr;
    HANDLE userToken = INVALID_HANDLE_VALUE;

    if (options.e)
    {
        OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &userToken);
        CreateEnvironmentBlock(
            reinterpret_cast<LPVOID *>(&environment),
            userToken,
            FALSE
        );
        CloseHandle(userToken);
    }


    BOOL noError;
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInformation;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    startupInfo.dwFlags = STARTF_USESHOWWINDOW;
    startupInfo.wShowWindow = SW_HIDE;
    noError = CreateProcess(
        NULL,											//lpApplicationName
        const_cast<LPWSTR>(commandLine.c_str()),		//lpCommandLine
        NULL,											//lpProcessAttributes
        NULL,											//lpThreadAttributes
        FALSE,											//bInheritHandles
        CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT,	//dwCreationFlags
        options.e ? environment : NULL,					//lpEnvironment
        NULL,											//lpCurrentDirectory
        &startupInfo,									//lpStartupInfo
        &processInformation								//lpProcessInformation
    );

    if(!noError)
    {
        return GetLastError();
    }
    
    DWORD exitCode = 0;
    
    if (options.w)
    {
        WaitForSingleObject(processInformation.hProcess, INFINITE);
        if (GetExitCodeProcess(processInformation.hProcess, &exitCode) == 0)
        {
            exitCode = (DWORD)-1;
        }
    }

    CloseHandle( processInformation.hProcess );
    CloseHandle( processInformation.hThread );
    if (options.e)
    {
        DestroyEnvironmentBlock(static_cast<LPVOID>(environment));
    }

    return (int) exitCode;
}