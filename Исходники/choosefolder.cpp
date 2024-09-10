//---------------------------------------------------------------------------
EasyStr ChooseFolder(HWND Win,char *Title,char *FolToSel)
{
    ITEMIDLIST *RetIDL,*RootIDL=NULL;
    char FolName[MAX_PATH+1];
    IMalloc *Mal;
    BROWSEINFO bi;

    SHGetMalloc(&Mal);

    bi.hwndOwner=Win;
    bi.pidlRoot=RootIDL;              //Directory to start from (NULL=desktop)
    bi.pszDisplayName=FolName;        //Doesn't return full path
    bi.lpszTitle=Title;
    bi.ulFlags=BIF_RETURNONLYFSDIRS;  //No false folders (like DUN)
    bi.lpfn=ChooseFolder_BrowseCallbackProc; // Function to handle various notification
    bi.lParam=(LPARAM)FolToSel;         // What to call that func with
    bi.iImage=0;

    RetIDL=SHBrowseForFolder(&bi);
    if (RetIDL==NULL) return "";

    EasyStr SelFol;
    SelFol.SetLength(MAX_PATH);
    SHGetPathFromIDList(RetIDL,SelFol);
    NO_SLASH(SelFol);

    Mal->Free(RetIDL);

    return SelFol;
}