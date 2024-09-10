int keysWin32(char *dirname, char ***keys, int *nkeys)
{
	int rc = 0;
	char **fkeys = NULL;
	int nfkeys = 0;
	char dir[MAX_PATH+1];
	WIN32_FIND_DATAA FileData;
	HANDLE hDir;
	int fFinished = 0;
	char *ptraux;
	int i;

	FUNC_ENTRY;
	sprintf(dir, "%s/*", dirname);

	/* get number of keys */
	hDir = FindFirstFileA(dir, &FileData);
	if (hDir != INVALID_HANDLE_VALUE)
	{
		while (!fFinished)
		{
			if (FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
				nfkeys++;
			if (!FindNextFileA(hDir, &FileData))
			{
				if (GetLastError() == ERROR_NO_MORE_FILES)
					fFinished = 1;
			}
		}
		FindClose(hDir);
	} else
	{
		rc = MQTTCLIENT_PERSISTENCE_ERROR;
		goto exit;
	}

	if (nfkeys != 0 )
		fkeys = (char **)malloc(nfkeys * sizeof(char *));

	/* copy the keys */
	hDir = FindFirstFileA(dir, &FileData);
	if (hDir != INVALID_HANDLE_VALUE)
	{
		fFinished = 0;
		i = 0;
		while (!fFinished)
		{
			if (FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
			{
				fkeys[i] = malloc(strlen(FileData.cFileName) + 1);
				strcpy(fkeys[i], FileData.cFileName);
				ptraux = strstr(fkeys[i], MESSAGE_FILENAME_EXTENSION);
				if ( ptraux != NULL )
					*ptraux = '\0' ;
				i++;
			}
			if (!FindNextFileA(hDir, &FileData))
			{
				if (GetLastError() == ERROR_NO_MORE_FILES)
					fFinished = 1;
			}
		}
		FindClose(hDir);
	} else
	{
		rc = MQTTCLIENT_PERSISTENCE_ERROR;
		goto exit;
	}

	*nkeys = nfkeys;
	*keys = fkeys;
	/* the caller must free keys */

exit:
	FUNC_EXIT_RC(rc);
	return rc;
}