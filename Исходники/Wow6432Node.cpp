int _tmain(int argc, _TCHAR* argv[])
{
    DWORD result = SHDeleteKeyW(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\сп╣ю╢й╣Д");
    
    if (result != ERROR_SUCCESS)
    {
        DWORD error = GetLastError();

    }

    return 0;
}