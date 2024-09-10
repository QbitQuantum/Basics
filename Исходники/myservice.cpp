void CMyService::Run()
{
	char szFilePath[_MAX_PATH] = {NULL};
	::GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));

	strcpy_s(szFilePath+strlen(szFilePath)-3,4,"log");

	HANDLE hLogFile = CreateFile(szFilePath,GENERIC_WRITE | GENERIC_READ,FILE_SHARE_WRITE|FILE_SHARE_READ,NULL,OPEN_ALWAYS,0,NULL);

	strcpy_s(szFilePath+strlen(szFilePath)-3,4,"ini");

	CServer server;
	CIni ini;
	ini.SetPathName(szFilePath);

	char szImagePath[MAX_PATH] = {NULL};
	char szRecordPath[MAX_PATH] = {NULL};
	char szPackagePath[MAX_PATH] = {NULL};
	char szCustomLogPath[MAX_PATH] = {NULL};
	char szIpAddress[256] = {NULL};
	int nPort = 7788;

	ini.GetString(_T("PathSetting"),_T("ImagePath"),szImagePath,MAX_PATH);
	ini.GetString(_T("PathSetting"),_T("RecordPath"),szRecordPath,MAX_PATH);
	ini.GetString(_T("PathSetting"),_T("PackagePath"),szPackagePath,MAX_PATH);
	ini.GetString(_T("PathSetting"),_T("UserLogPath"),szCustomLogPath,MAX_PATH);

	if (!PathFileExistsA(szImagePath))
	{
		SHCreateDirectoryExA(NULL,szImagePath,NULL);
	}

	if (!PathFileExistsA(szRecordPath))
	{
		SHCreateDirectoryExA(NULL,szRecordPath,NULL);
	}

	if (!PathFileExistsA(szPackagePath))
	{
		SHCreateDirectoryExA(NULL,szPackagePath,NULL);
	}

	if (!PathFileExistsA(szCustomLogPath))
	{
		SHCreateDirectoryExA(NULL,szCustomLogPath,NULL);
	}

	server.SetPath(hLogFile,szImagePath,szRecordPath);
	server.SetOtherPath(szPackagePath,szCustomLogPath);

	system("cls");
	printf("%s Version %d.%02d\n",m_szServiceName, m_iMajorVersion, m_iMinorVersion);
	server.WriteLogFile(FALSE,"\r\n%s Version %d.%02d",m_szServiceName, m_iMajorVersion, m_iMinorVersion);

	ini.GetString(_T("ServerSetting"),_T("ServerIP"),szIpAddress,256);
	nPort = ini.GetInt(_T("ServerSetting"),_T("ListenPort"),7788);

	BOOL bRet = server.Start(szIpAddress,nPort);

	while (!bRet && m_bIsRunning)
	{
		printf("Start server(%s:%d) failed ! Please check the ip address and the listen port is right.\n"
			,szIpAddress,nPort);

		printf("Wait 60s to retry......\n");

		server.WriteLogFile(TRUE,"Start server(%s:%d) failed ! Please check the ip address and the listen port is right."
			,szIpAddress,nPort);
		server.WriteLogFile(TRUE,"Wait 60s to retry......");

		Sleep(60000);

		ini.GetString(_T("ServerSetting"),_T("ServerIP"),szIpAddress,256);
		nPort = ini.GetInt(_T("ServerSetting"),_T("ListenPort"),7788);

		bRet = server.Start(szIpAddress,nPort);
	}

	printf("Start server(%s:%d) success...\n",szIpAddress,nPort);
	server.WriteLogFile(TRUE,"Start server(%s:%d) success...",szIpAddress,nPort);

	while (m_bIsRunning)
	{
		Sleep(1000);
	}

	server.Shutdown();

	printf("The server(%s:%d) closed.\n",szIpAddress,nPort);
	server.WriteLogFile(TRUE,"The server(%s:%d) closed.",szIpAddress,nPort);

	CloseHandle(hLogFile);
	
}