void GetDrives (CDriveArray &array)
{
	array.clear ();

	IShellFolder   *psfDesktop;

	SHGetDesktopFolder(&psfDesktop);
	if(psfDesktop == NULL)
		return;
	
	LPITEMIDLIST   pidlMyComputer;

	SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &pidlMyComputer);

	if(pidlMyComputer == NULL)
	{
		psfDesktop->Release();
		return;
	}
	
	IShellFolder   *psfMyComputer;

	psfDesktop->BindToObject(pidlMyComputer, NULL, IID_IShellFolder, (LPVOID*)&psfMyComputer);
	
	if(psfMyComputer)
	 {
			IEnumIDList* pEnum;
			if(SUCCEEDED(psfMyComputer->EnumObjects(NULL, SHCONTF_FOLDERS|SHCONTF_INCLUDEHIDDEN, &pEnum)))
			{
				ITEMIDLIST* pidl;
				DWORD  dwFetched = 1;
				TCHAR  path[MAX_PATH];

				while(SUCCEEDED(pEnum->Next(1, &pidl, &dwFetched)) && dwFetched)
				{
					SHFILEINFO     sfi;	
					
					//LPITEMIDLIST pidl_full = Pidl_Concatenate (pidlMyComputer, pidl);
					LPITEMIDLIST pidl_full = ILCombine (pidlMyComputer, pidl);					
					SHGetPathFromIDList (pidl_full, path);

					UINT nType = GetDriveType( path);
				//	if( DRIVE_REMOVABLE < nType && nType <= DRIVE_RAMDISK )
					if( nType != DRIVE_UNKNOWN && nType != DRIVE_NO_ROOT_DIR )
					if(SHGetFileInfo((LPCTSTR)pidl_full, 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_DISPLAYNAME | SHGFI_TYPENAME | SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_LINKOVERLAY))
					{
						CDriveInfo info;
						info.m_Name = sfi.szDisplayName;
						info.m_Path = path;
						info.m_Type = sfi.szTypeName;
						info.m_nImage = sfi.iIcon;
						info.m_nType = nType;
						
						DWORD SectorsPerCluster;     // sectors per cluster
						DWORD BytesPerSector;        // bytes per sector
						DWORD NumberOfFreeClusters;  // free clusters
						DWORD TotalNumberOfClusters; // total clusters
					//	TRACE (L"%s %s\n", sfi.szDisplayName, path);		
						if (nType != DRIVE_REMOVABLE )
						if (GetDiskFreeSpace (path, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters))
							{	
									DWORD BytesPerCluster = BytesPerSector * SectorsPerCluster;								
									info.m_FreeSpace = UInt32x32To64(NumberOfFreeClusters, BytesPerCluster);
									info.m_TotalSize= UInt32x32To64(TotalNumberOfClusters, BytesPerCluster);
							}
						array.push_back (info);
					}
				}
				pEnum->Release ();
			}
		 psfMyComputer->Release();
	 }

	
	CoTaskMemFree(pidlMyComputer);
	
	psfDesktop->Release();    	
}