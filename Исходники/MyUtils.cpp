BOOL CMyUtils::GetSpecialFolder(int nFolder, TCHAR strFolder[MAX_PATH])
{
	TCHAR	*p = NULL;
	
	LPITEMIDLIST	pidl = NULL;
	IMalloc	*pMalloc = NULL;
	BOOL	bRet = FALSE;
	
	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
	{
		pMalloc->AddRef();
		SHGetSpecialFolderLocation(NULL, nFolder, &pidl);
		
		if (pidl)
        {                      
			bRet = SHGetPathFromIDList(pidl, strFolder);
            // Free the PIDL returned by SHGetSpecialFolderLocation.
           pMalloc->Free(pidl);
        }

        // Release the IMalloc interface.
        pMalloc->Release();
    }

	return bRet;
}