plFileName plBrowseFolder::GetFolder(const plFileName &startPath, const ST::string &title, HWND hwndOwner)
{
    BROWSEINFOW bi;
    memset(&bi, 0, sizeof(bi));
    ST::wchar_buffer titleW = title.to_wchar();
    ST::wchar_buffer startPathW = startPath.WideString();
    bi.hwndOwner    = hwndOwner;
    bi.lpszTitle    = titleW.data();
    bi.lpfn         = BrowseCallbackProc;
    bi.lParam       = (LPARAM) startPathW.data();

    LPITEMIDLIST iil = SHBrowseForFolderW(&bi);
    plFileName path;
    if (!iil) {
        // Browse failed, or cancel was selected
        path = ST::null;
    } else {
        // Browse succeded.  Get the path.
        wchar_t buffer[MAX_PATH];
        SHGetPathFromIDListW(iil, buffer);
        path = ST::string::from_wchar(buffer);
    }

    // Free the memory allocated by SHBrowseForFolder
    LPMALLOC pMalloc;
    SHGetMalloc(&pMalloc);
    pMalloc->Free(iil);
    pMalloc->Release();

    return path;
}