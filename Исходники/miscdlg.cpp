/*
	ディレクトリダイアログ用汎用ルーチン
*/
BOOL BrowseDirDlg(TWin *parentWin, const char *title, const char *defaultDir, char *buf)
{ 
	IMalloc			*iMalloc = NULL;
	BROWSEINFOW		brInfo;
	LPITEMIDLIST	pidlBrowse;
	BOOL			ret = FALSE;
	Wstr			buf_w(MAX_PATH), defaultDir_w(MAX_PATH), title_w(title);

	if (!SUCCEEDED(SHGetMalloc(&iMalloc)))
		return FALSE;

	U8toW(defaultDir, defaultDir_w.Buf(), MAX_PATH);
	brInfo.hwndOwner = parentWin->hWnd;
	brInfo.pidlRoot = 0;
	brInfo.pszDisplayName = buf_w.Buf();
	brInfo.lpszTitle = title_w;
	brInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	brInfo.lpfn = BrowseDirDlgProc;
	brInfo.lParam = (LPARAM)defaultDir_w.Buf();
	brInfo.iImage = 0;

	if ((pidlBrowse = SHBrowseForFolderV((BROWSEINFO *)&brInfo)))
	{
		ret = SHGetPathFromIDListV(pidlBrowse, buf_w.Buf());
		iMalloc->Free(pidlBrowse);
		if (ret)
			WtoU8(buf_w, buf, MAX_PATH_U8);
	}

	iMalloc->Release();
	return	ret;
}