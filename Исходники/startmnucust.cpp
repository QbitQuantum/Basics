VOID OnAdvancedStartMenuItems()
{
    WCHAR szPath[MAX_PATH];

    if(SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_STARTMENU, NULL, 0, szPath)))
    {
        ShellExecuteW(NULL, L"explore", szPath, NULL, NULL, SW_SHOWNORMAL);
    }
}