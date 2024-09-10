AnsiString GetSystemPath(int nFolder)
{
    char StartPath[MAXPATH];
    LPITEMIDLIST pidl;
    SHGetSpecialFolderLocation(Application->Handle, nFolder , &pidl); //CSIDL_STARTUP, CSIDL_STARTMENU, CSIDL_PROGRAMS
    SHGetPathFromIDList(pidl, StartPath);
    return AnsiString(StartPath);
}