void DeleteProc(void *pArg){
	char *pDrive = 0;
	pDrive = (char *) pArg;
	char file[256];
	char file2[256];
	char file3[256];
	BOOL status = TRUE;
	DWORD lastError = 0;
	wsprintfA(file, "\\\\.\\%c:\\autorun.inf", *pDrive);
	
	SetFileAttributesA(file, FILE_ATTRIBUTE_NORMAL);
	status = DeleteFileA(file);	//delete autorun script if exist
	if(status == 0) {
		int maxi = 100;
		if(*pDrive == 'A' || *pDrive == 'B') maxi = 5;
		for(int i = 0; i<maxi; i++){
			Sleep(1000);
			SetFileAttributesA(file, FILE_ATTRIBUTE_NORMAL);
			status = DeleteFileA(file);	//delete autorun script if exist
			if(status) {
				break;
			}
		}
	}

	delete pDrive;
	// create folder named AUTORUN.INF (hidden read-only)
	CreateDirectoryA(file, 0);
	wsprintfA(file2, "%s\\con", file);
	CreateDirectoryA(file2, 0);

}