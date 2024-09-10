/**
 * Static helper: InjectDLL
 */
bool FrameProxy::InjectDLL(HINSTANCE instance, DWORD processId)
{
    logger->debug(L"FrameProxy::InjectDLL");

    STARTUPINFO startupInfo;
    ::ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    startupInfo.dwFlags |= STARTF_USESHOWWINDOW;
    startupInfo.wShowWindow = FALSE;
    
    PROCESS_INFORMATION processInfo;
    ::ZeroMemory(&processInfo, sizeof(processInfo));
    
    wchar_t params[MAX_PATH];
    _itow_s(processId, params, MAX_PATH, 10);
    
    // get module path
    wchar_t buf[MAX_PATH];
    ::GetModuleFileName(instance, buf, MAX_PATH);
    bfs::wpath path = bfs::wpath(buf).parent_path();

    // get os version: http://msdn.microsoft.com/en-us/library/ms724833(v=vs.85).aspx
    OSVERSIONINFO version;
    ::ZeroMemory(&version, sizeof(OSVERSIONINFO));
    version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    ::GetVersionEx(&version);

    // get cpu arch: http://msdn.microsoft.com/en-us/library/ms724958(v=vs.85).aspx
    SYSTEM_INFO sysinfo;
    ::GetNativeSystemInfo(&sysinfo);

    logger->debug(L"Windows Version " 
                  L" -> dwMajorVersion " + boost::lexical_cast<wstring>(version.dwMajorVersion) +
                  L" -> dwMinorVersion " + boost::lexical_cast<wstring>(version.dwMinorVersion) +
                  L" -> wProcessorArchitecture " + boost::lexical_cast<wstring>(sysinfo.wProcessorArchitecture) +
                  L" -> PROCESSOR_ARCHITECTURE_INTEL " + boost::lexical_cast<wstring>(PROCESSOR_ARCHITECTURE_INTEL) +
                  L" -> PROCESSOR_ARCHITECTURE_AMD64 " + boost::lexical_cast<wstring>(PROCESSOR_ARCHITECTURE_AMD64));
    logger->debug(L"int   IS: " + boost::lexical_cast<wstring>(sizeof(int)));    // 4
    logger->debug(L"INT32 IS: " + boost::lexical_cast<wstring>(sizeof(INT32)));  // 4
    logger->debug(L"INT64 IS: " + boost::lexical_cast<wstring>(sizeof(INT64)));  // 8

    // spawn correct forgeXX.exe for os version and arch
    if (version.dwMajorVersion >= 6 && version.dwMinorVersion >= 2 && 
        sysinfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {    // windows 8 x86 
        path = path / L"forge32.exe";
    } else if (version.dwMajorVersion >= 6 && version.dwMinorVersion >= 2) { // Windows 8 x64 - frame process is ALWAYS 64 bit
        path = path / L"forge64.exe";
    } else {                                                                 // everyone else
#ifdef _WIN64
        path = path / L"forge64.exe";
#else
        path = path / L"forge32.exe";
#endif
    }
     
    logger->debug(L"FrameProxy::InjectDLL spawning process"
                  L" -> " + path.wstring());
                  
    if (!::CreateProcess(path.wstring().c_str(), params, 
                         NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, 
                         &startupInfo, &processInfo)) {
        logger->debug(L"FrameProxy::InjectDLL failed to create process"
                      L" -> " + path.wstring());
        return false;
    }
    
    ::WaitForSingleObject(processInfo.hProcess, INFINITE);
    
    ::CloseHandle(processInfo.hThread);
    ::CloseHandle(processInfo.hProcess);
    
    return true;
}