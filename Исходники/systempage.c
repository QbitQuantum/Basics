static BOOL
InitializeSystemDialog(HWND hDlg)
{
    WCHAR winDir[PATH_MAX];

    GetWindowsDirectoryW(winDir, PATH_MAX);
    return LoadSystemIni(winDir, hDlg);
}