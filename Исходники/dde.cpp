static DWORD CALLBACK DDE_OnViewFolder(PWSTR strCommand, PWSTR strPath, LPITEMIDLIST pidl, INT unkS)
{
    if (!pidl)
        pidl = ILCreateFromPathW(strPath);

    if (!pidl)
        return DDE_FNOTPROCESSED;

    if (FAILED(SHOpenNewFrame(pidl, NULL, 0, 0)))
        return DDE_FNOTPROCESSED;

    return DDE_FACK;
}