bool Platform::killProcess(const std::string& name)
{
    HWND window = FindWindowA(name.c_str(), NULL);
    if(window == NULL)
        return false;
    DWORD pid = GetProcessId(window);
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if(handle == NULL)
        return false;
    bool ok = TerminateProcess(handle, 1) != 0;
    CloseHandle(handle);
    return ok;
}