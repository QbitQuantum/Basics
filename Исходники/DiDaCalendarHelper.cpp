static BOOL MyIsWow64Process(HANDLE hProcess, PBOOL Wow64Process)
{
	typedef BOOL (WINAPI* IsWow64Process_FuncType)(HANDLE hProcess, PBOOL Wow64Process);
	IsWow64Process_FuncType isWow64Process = reinterpret_cast<IsWow64Process_FuncType>(::GetProcAddress(::GetModuleHandle(L"kernel32.dll"), "IsWow64Process"));
	if(isWow64Process == NULL) {
		*Wow64Process = FALSE;
		return TRUE;
	}
	BOOL ret = isWow64Process(hProcess, Wow64Process);
	return ret;
}