void RotateLogs()
{
	char tmpNo[3] = {0};
	char oldDirNo;
	char baseDirName[256] = {0};
	char oldDirName[256] = {0};
	char newDirName[256] = {0};
	char tmpFileName[256] = {0};

	if (strlen(GetLogDir()) == 0)
		return;

	GetCurrentDirectoryA(256, baseDirName);
	strcat(baseDirName, "\\");
	strcat(baseDirName, GetLogDir());
	strcat(baseDirName, "\\");

	// Delete directory '9'
	strcpy(oldDirName, baseDirName);
	strcat(oldDirName, "9");

	SHFILEOPSTRUCTA fileOp;
	fileOp.hwnd = 0;
	fileOp.wFunc = FO_DELETE;
	fileOp.pFrom = oldDirName;
	fileOp.pTo = NULL;
	fileOp.fFlags = FOF_NOERRORUI + FOF_NOCONFIRMATION;
    fileOp.fAnyOperationsAborted = NULL;
    fileOp.hNameMappings = NULL;
    fileOp.lpszProgressTitle = NULL;

	SHFileOperationA(&fileOp);

	// Age directories 1-8
	for (oldDirNo = 99; oldDirNo > 0; oldDirNo--)
	{
		strcpy(oldDirName, baseDirName);
		_itoa(oldDirNo, tmpNo, 10);
		strcat(oldDirName, tmpNo);
		strcpy(newDirName, baseDirName);
		_itoa(oldDirNo + 1, tmpNo, 10);
		strcat(newDirName, tmpNo);
		MoveFileA(oldDirName, newDirName);
	}

	// Create youngest directory '1'
	CreateDirectoryA(oldDirName, NULL);

	// Move current log files to '1'
	strcpy(oldDirName, baseDirName);
	strcat(oldDirName, "nwnx.txt");
	strcpy(newDirName, baseDirName);
	strcat(newDirName, "1\\nwnx.txt");
	MoveFileA(oldDirName, newDirName);
	strcpy(oldDirName, baseDirName);
	strcat(oldDirName, "nwserverlog1.txt");
	strcpy(newDirName, baseDirName);
	strcat(newDirName, "1\\nwserverlog1.txt");
	MoveFileA(oldDirName, newDirName);
	strcpy(oldDirName, baseDirName);
	strcat(oldDirName, "nwserverError1.txt");
	strcpy(newDirName, baseDirName);
	strcat(newDirName, "1\\nwserverError1.txt");
	MoveFileA(oldDirName, newDirName);

	strcpy(oldDirName, baseDirName);
	strcat(oldDirName, "nwnx_odbc.txt");
	strcpy(newDirName, baseDirName);
	strcat(newDirName, "1\\nwnx_odbc.txt");
	MoveFileA(oldDirName, newDirName);
}