static int CountRunnings()
{
	HANDLE h;
	PROCESSENTRY32W pe;

	h=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);
	pe.dwSize=sizeof(pe);
	Process32FirstW(h,&pe);

	String szModule = GetModuleName(0);

	int Count=0;
	while(true)
	{
		if(!_wcsicmp(L"dcmap.exe",pe.szExeFile))
		{
			  HANDLE h;
			  MODULEENTRY32 mdl;
			  h=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,pe.th32ProcessID);
			  mdl.dwSize=sizeof(MODULEENTRY32);
			  Module32First(h,&mdl);
			  while(1)
			  {
				if(szModule == mdl.szExePath)
				{
					Count++;
					break;
				}
				if (!Module32Next(h,&mdl)) break;
			  }
			  CloseHandle(h);
		}
		if (!Process32NextW(h,&pe)) break;
	  }
	  return Count;
}