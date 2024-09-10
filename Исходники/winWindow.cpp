void WinWindow::doRunOnStart()
{
    std::string runPath = "\"" + getExecutablePath() + "\" -m";

    Helper::request_privileges(SE_TAKE_OWNERSHIP_NAME);

    HKEY hKey;
    LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey);
    if (result == ERROR_SUCCESS)
    {
        if ((result = RegSetValueExA( hKey, "NOSA-Server", 0, REG_SZ, (BYTE*)runPath.c_str(), runPath.length())) == ERROR_SUCCESS)
            MessageBox(NULL, "Now NOSA-Server service will launch of computer start.", "Done!", MB_ICONINFORMATION | MB_OK);
        else
            MessageBox(NULL, "You don't have sufficient rights to edit your registry. Please try run this application with admin privilege.", "Error!",  MB_ICONERROR | MB_OK);
    }
    else
        MessageBox(NULL, "Your registry has wrong format!", "Error!", MB_ICONERROR | MB_OK);

    RegCloseKey(hKey);
    return;
}