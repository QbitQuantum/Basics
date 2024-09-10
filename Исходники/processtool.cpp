vector<MODULEENTRY32> CProcessTool::GetProcessModules(DWORD dwPID)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	VCTMOD vctMod;

	hModuleSnap =  CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,dwPID);

	memset(&me32,0,sizeof(me32));
	if( hModuleSnap == INVALID_HANDLE_VALUE)
	{
		LOG::printError(TEXT("CreateToolhelp32Snapshot (od modules)"));
		return vctMod;
	}


	me32.dwSize = sizeof(MODULEENTRY32);

	if(!Module32First(hModuleSnap,&me32))
	{
		LOG::printError(TEXT("Module32First"));
		CloseHandle(hModuleSnap);
		return vctMod;
	}

	do 
	{
		vctMod.push_back(me32);

	} while (Module32Next(hModuleSnap,&me32));

	CloseHandle(hModuleSnap);
	return vctMod;

}