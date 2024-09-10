CString CFilePro::GetSelectedFolder()
{
	BROWSEINFO bi;  
	ZeroMemory(&bi,sizeof(BROWSEINFO));  
	LPMALLOC pMalloc;  
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);  

	if(!pidl )
	{
		m_strErrMsg = "用户取消";
		return "";
	}

	CString strFolderOut = "";
	TCHAR * path = new TCHAR[MAX_PATH];   

	SHGetPathFromIDList(pidl,path);  
	if(SUCCEEDED(SHGetMalloc(&pMalloc))) 
	{  
		pMalloc->Free(pidl);  
		pMalloc->Release();  
	}

	strFolderOut = path;
	delete [] path;
	return strFolderOut;
}