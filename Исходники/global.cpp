CString AfxGetDefaultDirectory(bool bForceNonEmpty /*= true*/,bool bNewProject /*= false*/)
{
	////////////////////////
	//Get default directory
	CString strPersonalDir;

	// - New Project?
	if (!bNewProject)
	{
		// - Get LastOpenedFolder
		strPersonalDir = CConfiguration::GetInstance()->m_strLastOpenedFolder;
		if (strPersonalDir.IsEmpty() || !CPathTool::Exists(strPersonalDir))
		{
			// - Project opened? ==> Working Dir is default
			CLaTeXProject* pLProject = theApp.GetProject();
			if (pLProject) strPersonalDir = pLProject->GetWorkingDirectory();
		}
	}

	// - No Project? ==> Try it with the default dir from the config
	if (strPersonalDir.IsEmpty())
	{
		strPersonalDir = CConfiguration::GetInstance()->m_strDefaultPath;
	}

	// - Still empty? ==> Get the system default for "My documents"
	if (strPersonalDir.IsEmpty())
	{
		LPITEMIDLIST lpidl;
		if (SHGetSpecialFolderLocation(AfxGetMainWnd()->m_hWnd,CSIDL_PERSONAL,&lpidl) == NOERROR)
		{
			SHGetPathFromIDList(lpidl,strPersonalDir.GetBuffer(MAX_PATH));
			strPersonalDir.ReleaseBuffer();

			// free memory
			LPMALLOC lpMalloc;
			SHGetMalloc(&lpMalloc);
			if (lpMalloc)
				lpMalloc->Free(lpidl);
		}
	}


	// - Still empty? ==> Hell, this is hard. Lets try this.
	if (bForceNonEmpty && strPersonalDir.IsEmpty())
	{
		strPersonalDir = theApp.GetWorkingDir();
	}

	// - Still empty? ==> Hell, this is hard. Lets try this.
	if (bForceNonEmpty && strPersonalDir.IsEmpty())
	{
		strPersonalDir = _T("C:\\");
	}

	return strPersonalDir;
}