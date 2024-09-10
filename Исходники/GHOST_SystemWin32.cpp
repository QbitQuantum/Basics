static DWORD GetParentProcessID(void)
{
	HANDLE snapshot;
	PROCESSENTRY32 pe32 = {0};
	DWORD ppid = 0, pid = GetCurrentProcessId();
	snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if (snapshot == INVALID_HANDLE_VALUE) {
		return -1;
	}
	pe32.dwSize = sizeof( pe32 );
	if (!Process32First(snapshot, &pe32)) {
		CloseHandle(snapshot);
		return -1;
	}
	do {
		if (pe32.th32ProcessID == pid) {
			ppid = pe32.th32ParentProcessID;
			break;
		}
	} while (Process32Next(snapshot, &pe32));
	CloseHandle(snapshot);
	return ppid;
}