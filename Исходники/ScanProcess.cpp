void CheckModule()
{
	MODULEENTRY32 ME32;
	HANDLE hProcessSnap;
	int ProcLoop;
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	ME32.dwSize = sizeof(ME32);
	ProcLoop = Module32First(hProcessSnap, &ME32);
	while(ProcLoop){
		ProcLoop = Module32Next(hProcessSnap, &ME32);
		char ModulePath[MAX_PATH];
		int len = GetModuleFileName(ME32.hModule, ModulePath, MAX_PATH);
		if(len != 0){
			for(int i = len - 1; i >= 0; i --)
			{
				if (ModulePath[i] == '\\')
				{
					if (cmpi(&ModulePath[i+1], "cfgdll.dll") == 0)
					{
						KillMe(3);
					}
					break;
				}
			}
		}
	}
	CloseHandle(hProcessSnap);
}