DWORD HookFunction(LPCSTR lpModule, LPCSTR lpFuncName, LPVOID lpFunction, unsigned char *lpBackup)
{
	DWORD dwAddr = (DWORD)GetProcAddress(GetModuleHandle(lpModule), lpFuncName);
	BYTE jmp[6] = { 0xe9,	//jmp
		0x00, 0x00, 0x00, 0x00,	//address
		0xc3
	};	//retn

	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, lpBackup, 6, 0);

	DWORD dwCalc = ((DWORD)lpFunction - dwAddr - 5);	//((to)-(from)-5)

	memcpy(&jmp[1], &dwCalc, 4);	//build the jmp

	WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, jmp, 6, 0);

	return dwAddr;
}