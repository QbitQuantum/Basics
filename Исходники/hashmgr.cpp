int CHashManager::HashPath(char *pszBasePath, char *pszFileSpec)
{
	recursivesafe long lHandle = 0;
	recursivesafe long lSearcherHandle = 0;
	recursivesafe finddata fdInfo;
	recursivesafe char szFull[RH_MAX_PATH];
	recursivesafe char szAll[RH_MAX_PATH];

	if(pszBasePath == NULL) return RH_INVALID_PATH;
	if(pszFileSpec == NULL) return RH_INVALID_PATH;

	fmtPath(pszBasePath);
	fmtPath(pszFileSpec);

	if(strlen(pszBasePath) == 0) getcwd(pszBasePath, RH_MAX_PATH);
	fileonly(pszFileSpec);

	strcpy(szAll, pszBasePath);
	catdirsep(szAll);
	strcat(szAll, SZ_DIR_ALL);

	#ifdef RH_DEBUG
		printf("Function HashPath: pszBasePath=%s, pszFileSpec=%s", pszBasePath, pszFileSpec);
		printf(CPS_NEWLINE);
		printf("Function HashPath: szAll=%s", szAll);
		printf(CPS_NEWLINE);
	#endif

	//////////////////////////////////////////////////////////////////////////
	// Start directory enumeration code

	lSearcherHandle = findfirst(szAll, &fdInfo);
	while(1)
	{
		if(fdInfo.attrib & _A_SUBDIR)
		{
			if((ispathnav(fdInfo.name) == false) && (m_bRecursive))
			{
				if(chdir(fdInfo.name) == 0)
				{
					getcwd(szFull, RH_MAX_PATH);

					#ifdef RH_DEBUG
						printf("Opening new scan path: %s, filemask: %s", szFull, pszFileSpec);
						printf(CPS_NEWLINE);
					#endif

					HashPath(szFull, pszFileSpec);
					chdir(SZ_LEVEL_UP);
				}
			}
		}

		if(findnext(lSearcherHandle, &fdInfo) != 0) break;
	}
	findclose(lSearcherHandle);
	lSearcherHandle = 0;

	// End directory enumeration code
	//////////////////////////////////////////////////////////////////////////

	memset(&fdInfo, 0, sizeof(finddata));
	lHandle = findfirst(pszFileSpec, &fdInfo);
	if(lHandle == EINVAL) return RH_INVALID_PATH;
	if(lHandle == ENOENT) return RH_NO_PATTERN_MATCH;
	if(lHandle == -1) return RH_CANNOT_OPEN_FILE;

	while(1)
	{
		if(fdInfo.attrib & _A_SUBDIR)
		{
			// Don't process directories here
		}
		else
		{
			if(m_bFullPath)
			{
				fullpath(szFull, fdInfo.name, RH_MAX_PATH);
				HashFile(szFull);
			}
			else
			{
				HashFile(fdInfo.name);
			}
			printf(CPS_NEWLINE);
		}

		if(findnext(lHandle, &fdInfo) != 0) break;
	}

	findclose(lHandle);
	lHandle = 0;

	return RH_SUCCESS;
}