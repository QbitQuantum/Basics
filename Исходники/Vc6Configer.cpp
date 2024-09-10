BOOL CVc6ConfigerApp::CheckProcessExist(CString strName, DWORD *pPID)
{
	BOOL bExist = FALSE;
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 info = {0};
	info.dwSize = sizeof(PROCESSENTRY32);
	BOOL bRet = Process32First(handle, &info);
	if( bRet ){
		do {
			if ( strName.Compare(info.szExeFile) == 0 ){
				if (pPID != NULL){
					*pPID = info.th32ProcessID;
				}
				bExist = TRUE;
				break;
			}
			bRet = Process32Next(handle, &info);
		} while( bRet );
		CloseHandle(handle);
	}
	return bExist;
}