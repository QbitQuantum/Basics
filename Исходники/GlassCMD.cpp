void StartGlassCMD()
{
	PROCESSENTRY32 pe32;
	HANDLE hProcessSnap = NULL;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	hProcessSnap = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0);
	for (Process32First (hProcessSnap, &pe32); Process32Next (hProcessSnap, &pe32);)
	{
		if (stricmp(pe32.szExeFile, "cmd.exe") == 0)
		{
			EnumWindows((WNDENUMPROC)EnumWndProc, pe32.th32ProcessID);
		}
	}
	CloseHandle(hProcessSnap);

}