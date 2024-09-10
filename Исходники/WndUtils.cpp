bool SelDirectory ( HWND hWnd, LPCTSTR strTitle, CString &strDir )  
{  
	BROWSEINFO bi;  
	char szDisplayName[MAX_PATH] = {0};  

	bi.hwndOwner = hWnd;  
	bi.pidlRoot = NULL;  
	bi.pszDisplayName = szDisplayName;  
	bi.lpszTitle = strTitle;  
	bi.ulFlags = 0;  
	bi.lpfn = BrowserCallbackProc;  
	bi.lParam = (LPARAM)(LPCTSTR)strDir;  
	bi.iImage = NULL;  

	// 显示目录选择对话框，如果按了取消，那么piid为NULL  
	ITEMIDLIST* piid = ::SHBrowseForFolder ( &bi );  

	if ( piid == NULL )  return false;  

	// 得到选择的目录  
	BOOL bValidPath = ::SHGetPathFromIDList ( piid, szDisplayName );  
	if ( ! bValidPath ) return false;  

	LPMALLOC lpMalloc;  
	HRESULT hr = ::SHGetMalloc ( &lpMalloc );
	assert(hr == NOERROR);  
	lpMalloc->Free ( piid );  
	lpMalloc->Release ();  

	if ( szDisplayName[0] == '\0' ) return false; //用户选择的可能的虚拟文件系统  

	strDir = szDisplayName;  

	return true;
}