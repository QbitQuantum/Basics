BOOL BrowseForFolder(HWND hWnd, CString& strTitle, CString& strResult, BOOL bIncludeFiles, _tBrowseCallbackProc pCallback)
{
	BOOL bRet = FALSE;
    WCHAR szFolder[MAX_PATH * 2];
	
	ZeroMemory(szFolder, sizeof(szFolder));
	
    BROWSEINFO info;
    LPSHELLFOLDER shell;
    LPITEMIDLIST FolderID;
	
    SHGetDesktopFolder(&shell);
	
    info.hwndOwner = hWnd;
    info.pidlRoot = NULL;
    info.pszDisplayName = szFolder;
    info.lpszTitle = strTitle.GetBuffer(MAX_PATH);
    info.ulFlags = BIF_NEWDIALOGSTYLE;
	if (bIncludeFiles)
		info.ulFlags |= BIF_BROWSEINCLUDEFILES | BIF_NONEWFOLDERBUTTON;
    info.lpfn = pCallback;
	
    FolderID = SHBrowseForFolder(&info);
	
	if(FolderID != NULL)
	{
		if(SHGetPathFromIDList(FolderID, szFolder))
		{
			strResult= szFolder;
			bRet = TRUE;
		}
	}
	
    shell->Release();

	strTitle.ReleaseBuffer();
	
	return bRet;
}