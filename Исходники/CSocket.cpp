//----run process 
BOOL GetTokenByName(HANDLE &hToken,LPSTR lpName)
{
	if(!lpName)
	{
		return FALSE;
	}
	HANDLE         hProcessSnap = NULL; 
	BOOL           bRet      = FALSE; 
	PROCESSENTRY32 pe32      = {0}; 
	
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	if (hProcessSnap == INVALID_HANDLE_VALUE) 
		return (FALSE); 
	
	pe32.dwSize = sizeof(PROCESSENTRY32); 
	
	if (Process32First(hProcessSnap, &pe32)) 
	{  
		do 
		{
			if(!strcmp(_strupr(pe32.szExeFile),_strupr(lpName)))
			{
				HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,
					FALSE,pe32.th32ProcessID);
				bRet = OpenProcessToken(hProcess,TOKEN_ALL_ACCESS,&hToken);
				CloseHandle (hProcessSnap); 
				return (bRet);
			}
		} 
		while (Process32Next(hProcessSnap, &pe32)); 
		bRet = TRUE; 
	} 
	else 
		bRet = FALSE;
	
	CloseHandle (hProcessSnap); 
	return (bRet);
}