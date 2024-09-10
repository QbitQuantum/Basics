Bool Find3DCoat()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	if(!hSnapshot)return false;	
	pe.dwSize = sizeof(pe);
	for(int i = Process32First(hSnapshot, &pe); i; i = Process32Next(hSnapshot, &pe))
	{
		HANDLE hModuleSnap = NULL;
		MODULEENTRY32 me;
		hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe.th32ProcessID);
		if(hModuleSnap == (HANDLE) -1)continue;
		me.dwSize = sizeof(MODULEENTRY32);
		if(Module32First(hModuleSnap, &me))
		{
			do
			{
				char temp[MAX_PATH];
				strcpy_s(temp,MAX_PATH, me.szExePath);
				_strupr_s(temp, MAX_PATH);
				int p = (int)strlen(temp);
				char c = 0;
				while(c != '\\' && c != '/' && p != 0)
				{
					c = temp[p--];
				}
				char* s = temp + p;
				strupr(s);
				if(strstr(s,"3D-COAT"))
				{
					return true;
				}
				break;
			}while(Module32Next(hModuleSnap, &me));
		}
	}
	CloseHandle(hSnapshot);
	return false;
}