//获取指定目录的IShellFolder接口    
IShellFolder *CFileSearch::GetIShellFolderByPath(LPTSTR path)   
{   
	IShellFolder *m_ShellFolderTopMost=NULL;   
	HRESULT hr=SHGetDesktopFolder(&m_ShellFolderTopMost);   
	if(FAILED(hr))   
	{   
		return NULL;   
	}   
	IShellFolder *m_pFolder;   
	LPITEMIDLIST pidlWorkDir=NULL;     
	OLECHAR strOleFilePath[MAX_PATH];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, path, -1, strOleFilePath, MAX_PATH );
	hr = m_ShellFolderTopMost->ParseDisplayName(NULL,NULL,strOleFilePath,NULL,&pidlWorkDir,NULL);      
	if(FAILED(hr))   
	{   
		return   NULL;      
	}   
	hr=m_ShellFolderTopMost->BindToObject(pidlWorkDir,NULL,IID_IShellFolder,(LPVOID*)&m_pFolder);     
	if(m_ShellFolderTopMost)m_ShellFolderTopMost->Release();   
	return m_pFolder;   
}   