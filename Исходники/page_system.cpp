BOOL PageSystem::BrowseForFolder(HWND hOwner, TCHAR* szTitle, TCHAR* szRetval)
{
    BROWSEINFO info;
    LPITEMIDLIST itemidlist;
    TCHAR szDirectory[_MAX_PATH];
    LPMALLOC pMalloc;
    memset(szDirectory, 0, _MAX_PATH * sizeof(TCHAR));

    if (::SHGetMalloc(&pMalloc) == NOERROR)
    {
        info.hwndOwner = hOwner;
        info.pidlRoot = NULL;
        info.pszDisplayName = szDirectory;
        info.lpszTitle = szTitle;
        info.ulFlags = 0;
        info.lpfn = NULL;

        itemidlist = SHBrowseForFolder(&info);
        if (itemidlist != NULL)
        {
            SHGetPathFromIDList(itemidlist, szRetval);
            pMalloc->Free(itemidlist);
            pMalloc->Release();
            return TRUE;
        }
        else // User clicked Cancel
        {
            pMalloc->Release();
            return FALSE;
        }
    }
    else
        return FALSE;
}