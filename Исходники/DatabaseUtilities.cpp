CString GetOLDDefaultDBName()
{
	CString csDefaultPath;
	LPMALLOC pMalloc;

	if(SUCCEEDED(::SHGetMalloc(&pMalloc))) 
	{ 
		LPITEMIDLIST pidlPrograms;

		SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidlPrograms);

		TCHAR string[MAX_PATH];
		SHGetPathFromIDList(pidlPrograms, string);

		pMalloc->Free(pidlPrograms);
		pMalloc->Release();

		csDefaultPath = string;		
		csDefaultPath += "\\Ditto\\";

		csDefaultPath += "DittoDB.mdb";
	}

	return csDefaultPath;
}