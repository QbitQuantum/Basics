bool DirectoryRefDialog(HWND hWnd,char *Result)
{
    bool r = false;
    LPMALLOC Memory;
    LPCSTR Buffer;
    LPITEMIDLIST Ret;
    LPITEMIDLIST Root;
    SHGetMalloc(&Memory);
    Buffer = (LPSTR)Memory->Alloc(1000);
    SHGetSpecialFolderLocation(hWnd,CSIDL_DESKTOP,&Root);
    ZeroMemory(&BI,sizeof(BROWSEINFO));
    BI.hwndOwner = hWnd;
    BI.pidlRoot = Root;
    BI.ulFlags = BIF_STATUSTEXT | BIF_RETURNONLYFSDIRS;
    BI.lpszTitle = "展開先を指定してください";
    BI.pszDisplayName = (LPSTR)Buffer;
    BI.lpfn = BrowseCallbackProc;
    Ret = SHBrowseForFolder(&BI);
    if (SHGetPathFromIDList(Ret,(LPSTR)Buffer))
    {
        lstrcpy(Result,Buffer);
        r = true;
    }
    Memory->Free(Ret);
    Memory->Free(Root);
    Memory->Free((void*)Buffer);
    return r;
}