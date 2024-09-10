// Check if a specified file exist
bool af_IsFileExist(const char * szRelativePath)
{
	// we must supply a relative path to GetFilePck function
	AFilePackage * pPackage = g_AFilePackMan.GetFilePck(szRelativePath);
	if( pPackage )
	{
		//	Get file entry
		AFilePackage::FILEENTRY FileEntry;
		int iEntryIndex;
		if (pPackage->GetFileEntry(szRelativePath, &FileEntry, &iEntryIndex))
			return true;
	}

	{	// not found in package, so test if exist on the disk, here we must use full path
		char	szFullPath[1024];
		sprintf(szFullPath, "%s/%s", g_szBaseDir, szRelativePath);

	#ifdef _WIN32
		if( INVALID_FILE_ATTRIBUTES != GetFileAttributesA(szFullPath) )
			return true;
	#else
		if (access(szFullPath, 0) == 0)
			return true;
	#endif
	}

	//try backup packages
	{
		AFilePackage * pPackage = g_AFilePackMan.GetFilePck(szRelativePath, true);
		if( pPackage )
		{
			//	Get file entry
			AFilePackage::FILEENTRY FileEntry;
			int iEntryIndex;
			if (pPackage->GetFileEntry(szRelativePath, &FileEntry, &iEntryIndex))
				return true;
		}
	}

	return false;
}