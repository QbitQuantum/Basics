DWORD CAppreciation::GetProcessIDForProcessName(LPCTSTR lpProcessName)
{

	HANDLE hProcess=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	HANDLE hModule;
	PROCESSENTRY32* pinfo=new PROCESSENTRY32;
	MODULEENTRY32* minfo=new MODULEENTRY32;
	pinfo->dwSize=sizeof(PROCESSENTRY32);
	minfo->dwSize=sizeof(MODULEENTRY32);
	BOOL report;
	TCHAR szName[MAX_PATH] = {0};
	_tcscpy_s(szName,lpProcessName);
	_tcsupr_s(szName);

	//	printf("ShowProcessPath with [ToolHelp API]\n\n");

	report=Process32First(hProcess,pinfo);

	while(report)
	{
		hModule=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,pinfo->th32ProcessID);
		//Module32First(hModule, minfo);
		_tcsupr_s(pinfo->szExeFile);
		if (NULL != _tcsstr(pinfo->szExeFile,szName))
			return pinfo->th32ProcessID;

		report=Process32Next(hProcess, pinfo); 

	}


	CloseHandle(hProcess);
	CloseHandle(hModule);
	delete minfo;
	delete pinfo;
	return 0;
} 