// setup baseMenuFolder
void MetaLauncher::setBaseMenuFolder()
{
    wchar_t path[MAX_PATH];

	if (m_clientconn->m_opts.m_menuLoc == MENULOC_MIXLOCAL) {
        if (SHGetFolderPathW(NULL, CSIDL_PROGRAMS, NULL, SHGFP_TYPE_CURRENT, path) != S_OK) {
            vnclog.Print(0, _T("Failed to get menu directory.\n"));
            return;
        }
        m_baseMenuFolder = new wchar_t[wcslen(path) + 1];
        wcscpy(m_baseMenuFolder, path);
    } else {
        if (SHGetFolderPathW(NULL, CSIDL_STARTMENU, NULL, SHGFP_TYPE_CURRENT, path) != S_OK) {
            vnclog.Print(0, _T("Failed to get menu directory.\n"));
            return;
        }
        m_baseMenuFolder = new wchar_t[wcslen(path) + wcslen(topMenuFolder) + wcslen(m_desktopFolderName) + 3];
        wcscpy(m_baseMenuFolder, path);
        wcscat(m_baseMenuFolder, L"\\");
        wcscat(m_baseMenuFolder, topMenuFolder);
        if (CreateDirectoryW(m_baseMenuFolder, NULL) == 0) {
            vnclog.Print(0, _T("Failed to create menu directory. (error %d)\n"), GetLastError());
            return;
        }
        if (m_clientconn->m_opts.m_menuLoc == MENULOC_SEPARATE) {
            wcscat(m_baseMenuFolder, L"\\");
            wcscat(m_baseMenuFolder, m_desktopFolderName);
            if (CreateDirectoryW(m_baseMenuFolder, NULL) == 0) {
                vnclog.Print(0, _T("Failed to create menu directory. (error %d)\n"), GetLastError());
                return;
            }
        }
    }
}