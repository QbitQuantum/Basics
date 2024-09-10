const string ProjectConfigDialog::browseFolder(const string baseDir)
{
    char buff[MAX_PATH + 1] = {0};
    WCHAR curr[MAX_PATH + 1] = {0};

    if (baseDir.length() > 0)
    {
        MultiByteToWideChar(CP_UTF8, 0, baseDir.c_str(), baseDir.length(), curr, MAX_PATH);
    }
    else
    {
        GetCurrentDirectory(MAX_PATH + 1, curr);
    }

    BROWSEINFOA bi = {0};
    bi.hwndOwner = m_hwndDialog;
    bi.pszDisplayName = buff;
    bi.lpszTitle = "Select Project Directory";
    bi.lParam = reinterpret_cast<LPARAM>(curr);
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NONEWFOLDERBUTTON | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseFolderCallback;

    PIDLIST_ABSOLUTE pid = SHBrowseForFolderA(&bi);
    if (pid)
    {
        SHGetPathFromIDListA(pid, buff);
        return string(buff);
    }
    else
    {
        return string("");
    }
}