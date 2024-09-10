int
CreateFileListInfo(FileListInfoPtr pFileListInfo, char* path, int flag)
{
	int pathLen, basePathLength;
	char *basePath, *pChar;
	WIN32_FIND_DATAA winFindData;
	HANDLE findHandle;

	if(path == NULL) {
		return FAILURE;
	}

	if(strlen(path) == 0) {
		/* In this case we will send the list of entries in ftp root*/
		sprintf(path, "%s%s", GetFtpRoot(), "/");
	}

	/* Create a search string, like C:\folder\* */

	pathLen = strlen(path);
	basePath = malloc(pathLen + 3);
	memcpy(basePath, path, pathLen);
	basePathLength = pathLen;
	basePath[basePathLength] = '\\';
	basePath[basePathLength + 1] = '*';
	basePath[basePathLength + 2] = '\0';

	/* Start a search */
	memset(&winFindData, 0, sizeof(winFindData));
	findHandle = FindFirstFileA(path, &winFindData);

	basePath[basePathLength] = '\0'; /* Restore to a basePath + \ */
	/* Convert \ to / */
	for(pChar = basePath; *pChar; pChar++) {
		if (*pChar == '\\') {
			*pChar = '/';
		}
	}

	/* While we can find a next file do...
	   But ignore \. and '.. entries, which are current folder and parent folder respectively */
	while(findHandle != INVALID_HANDLE_VALUE && winFindData.cFileName[0] == '.' && 
		(winFindData.cFileName[1] == '\0' || 
		(winFindData.cFileName[1] == '.' && winFindData.cFileName[2] == '\0'))) {
		char fullpath[PATH_MAX];
		fullpath[0] = 0;

		strncpy_s(fullpath, PATH_MAX, basePath, basePathLength);
		strncpy_s(fullpath + basePathLength, PATH_MAX - basePathLength, winFindData.cFileName, (int)strlen(winFindData.cFileName));

		if(IS_FOLDER(winFindData.dwFileAttributes)) {
			if (AddFileListItemInfo(pFileListInfo, winFindData.cFileName, -1, 0) == 0) {
				rfbLog("File [%s]: Method [%s]: Add directory %s in the"
					" list failed\n", __FILE__, __FUNCTION__, fullpath);
				continue;
			}
		} 
		else if(IS_REGULAR_FILE(winFindData.dwFileAttributes)) {
			if(flag) {
				unsigned int fileSize = (winFindData.nFileSizeHigh * (MAXDWORD+1)) + winFindData.nFileSizeLow;
				if(AddFileListItemInfo(pFileListInfo, winFindData.cFileName, fileSize, FILETIME_TO_TIME_T(winFindData.ftLastWriteTime)) == 0) {
					rfbLog("File [%s]: Method [%s]: Add file %s in the "
						"list failed\n", __FILE__, __FUNCTION__, fullpath);
					continue;
				}			
			}
		}

		if(FindNextFileA(findHandle, &winFindData) == 0) {
			FindClose(findHandle);
			findHandle = INVALID_HANDLE_VALUE;
		}
	}

	if(findHandle != INVALID_HANDLE_VALUE) {
		FindClose(findHandle);
	}

	free(basePath);
	
	return SUCCESS;
}