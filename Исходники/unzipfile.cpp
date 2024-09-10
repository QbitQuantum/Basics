bool extractCurrentFile(unzFile uf, TCHAR *ptszDestPath, TCHAR *ptszBackPath, bool ch)
{
	unz_file_info64 file_info;
	char filename[MAX_PATH], buf[8192];

	int err = unzGetCurrentFileInfo64(uf, &file_info, filename, sizeof(filename), buf, sizeof(buf), NULL, 0);
	if (err != UNZ_OK)
		return false;

	for (char *p = strchr(filename, '/'); p; p = strchr(p+1, '/'))
		*p = '\\';

	if (ch && !db_get_b(NULL, MODNAME "Files", StrToLower(ptrA(mir_strdup(filename))), 1))
		return true;

	TCHAR tszDestFile[MAX_PATH], tszBackFile[MAX_PATH];
	TCHAR *ptszNewName = mir_utf8decodeT(filename);
	if (ptszNewName == NULL)
		ptszNewName = mir_a2t(filename);

	if (!(file_info.external_fa & FILE_ATTRIBUTE_DIRECTORY)) {
		err = unzOpenCurrentFile(uf);
		if (err != UNZ_OK)
			return false;

		if (ptszBackPath != NULL) {
			PrepareFileName(tszDestFile, SIZEOF(tszDestFile), ptszDestPath, ptszNewName);
			PrepareFileName(tszBackFile, SIZEOF(tszBackFile), ptszBackPath, ptszNewName);
			BackupFile(tszDestFile, tszBackFile);
		}

		PrepareFileName(tszDestFile, SIZEOF(tszDestFile), ptszDestPath, ptszNewName);
		SafeCreateFilePath(tszDestFile);

		TCHAR *ptszFile2unzip;
		if (hPipe == NULL) // direct mode
			ptszFile2unzip = tszDestFile;
		else {
			TCHAR tszTempPath[MAX_PATH];
			GetTempPath( SIZEOF(tszTempPath), tszTempPath);
			GetTempFileName(tszTempPath, _T("PUtemp"), GetCurrentProcessId(), tszBackFile);
			ptszFile2unzip = tszBackFile;
		}

		HANDLE hFile = CreateFile(ptszFile2unzip, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, file_info.external_fa, 0);
		if (hFile == INVALID_HANDLE_VALUE)
			return false;
			
		while (true) {
			err = unzReadCurrentFile(uf, buf, sizeof(buf));
			if (err <= 0)
				break;

			DWORD bytes;
			if (!WriteFile(hFile, buf, err, &bytes, FALSE)) {
				err = UNZ_ERRNO;
				break;
			}
		}

		FILETIME ftLocal, ftCreate, ftLastAcc, ftLastWrite;
		GetFileTime(hFile, &ftCreate, &ftLastAcc, &ftLastWrite);
		DosDateTimeToFileTime(HIWORD(file_info.dosDate), LOWORD(file_info.dosDate), &ftLocal);
		LocalFileTimeToFileTime(&ftLocal, &ftLastWrite);
		SetFileTime(hFile, &ftCreate, &ftLastAcc, &ftLastWrite);

		CloseHandle(hFile);
		unzCloseCurrentFile(uf); /* don't lose the error */

		if (hPipe)
			SafeMoveFile(ptszFile2unzip, tszDestFile);
	}
	mir_free(ptszNewName);
	return true;
}