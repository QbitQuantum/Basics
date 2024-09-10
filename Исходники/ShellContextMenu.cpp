void CShellContextMenu::SetPath(const tstring& strPath)
{
	// free all allocated datas
	if(m_psfFolder && bDelete)
		m_psfFolder->Release();
	m_psfFolder = NULL;
	FreePIDLArray(m_pidlArray);
	m_pidlArray = NULL;

	// get IShellFolder interface of Desktop(root of shell namespace)
	IShellFolder* psfDesktop = NULL;
	SHGetDesktopFolder(&psfDesktop);

	// ParseDisplayName creates a PIDL from a file system path relative to the IShellFolder interface
	// but since we use the Desktop as our interface and the Desktop is the namespace root
	// that means that it's a fully qualified PIDL, which is what we need
	LPITEMIDLIST pidl = NULL;
	psfDesktop->ParseDisplayName(NULL, 0, (LPOLESTR)const_cast<TCHAR*>(strPath.c_str()), NULL, &pidl, NULL);

	// now we need the parent IShellFolder interface of pidl, and the relative PIDL to that interface
	typedef HRESULT (CALLBACK* LPFUNC)(LPCITEMIDLIST pidl, REFIID riid, void **ppv, LPCITEMIDLIST *ppidlLast);
	LPFUNC MySHBindToParent = (LPFUNC)GetProcAddress(LoadLibrary(_T("shell32")), "SHBindToParent");
	if(MySHBindToParent == NULL) return;

	MySHBindToParent(pidl, IID_IShellFolder, (LPVOID*)&m_psfFolder, NULL);

	// get interface to IMalloc (need to free the PIDLs allocated by the shell functions)
	LPMALLOC lpMalloc = NULL;
	SHGetMalloc(&lpMalloc);
	lpMalloc->Free(pidl);

	// now we need the relative pidl
	IShellFolder* psfFolder = NULL;
	HRESULT res = psfDesktop->ParseDisplayName (NULL, 0, (LPOLESTR)const_cast<TCHAR*>(strPath.c_str()), NULL, &pidl, NULL);
	if(res != S_OK) return;

	LPITEMIDLIST pidlItem = NULL;
	SHBindToParent(pidl, IID_IShellFolder, (LPVOID*)&psfFolder, (LPCITEMIDLIST*)&pidlItem);
	// copy pidlItem to m_pidlArray
	m_pidlArray = (LPITEMIDLIST *) realloc(m_pidlArray, sizeof (LPITEMIDLIST));
	int nSize = 0;
	LPITEMIDLIST pidlTemp = pidlItem;
	if(pidlTemp) //[+]PPA http://iceberg.leschat.net/forum/index.php?s=&showtopic=265&view=findpost&p=26331
 	 while(pidlTemp->mkid.cb)
	 {
		nSize += pidlTemp->mkid.cb;
		pidlTemp = (LPITEMIDLIST) (((LPBYTE) pidlTemp) + pidlTemp->mkid.cb);
	 }
	 LPITEMIDLIST pidlRet = (LPITEMIDLIST) calloc(nSize + sizeof (USHORT), sizeof (BYTE));
	 CopyMemory(pidlRet, pidlItem, nSize);
	 m_pidlArray[0] = pidlRet;
	//free(pidlItem);
	lpMalloc->Free(pidl);

	lpMalloc->Release();
	if(psfFolder) //[+]PPA http://iceberg.leschat.net/forum/index.php?showtopic=265&st=2320&#
	   psfFolder->Release();
	psfDesktop->Release();

	bDelete = true;	// indicates that m_psfFolder should be deleted by CShellContextMenu
}