bool CComDialog::PopFolderDlg(OUT char* path, IN char* title, IN BFFCALLBACK cb)
{ 
    BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));    

//初始化入口参数bi开始****************************
    bi.hwndOwner = _hwnd;//::AfxGetMainWnd()->GetSafeHwnd();
    bi.pidlRoot = NULL;
    bi.pszDisplayName = path;//此参数如为NULL则不能显示对话框
    bi.lpszTitle = title;
    bi.ulFlags = 0;
    bi.lpfn = cb;
/*    bi.iImage= IDR_MAINFRAME;*/
//初始化入口参数bi结束*****************************

    LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
    if (pIDList)
    {
        SHGetPathFromIDList(pIDList, path);
        //取得文件夹路径到Buffer里
		LPMALLOC lpMalloc;
		if (FAILED(SHGetMalloc(&lpMalloc))) 
			return false;
		//释放内存
		lpMalloc->Free(pIDList);
		lpMalloc->Release();

		return true;
    }
	else
	{
		return false;
	}
}