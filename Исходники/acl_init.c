static void get_main_thread_id(void)
{
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	THREADENTRY32 th32;
	DWORD currentPID;
	BOOL  bOk;

	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return;
	currentPID = GetCurrentProcessId();
	th32.dwSize = sizeof(THREADENTRY32);

	for (bOk = Thread32First(hThreadSnap, &th32); bOk;
		bOk = Thread32Next(hThreadSnap, &th32))
	{
		if (th32.th32OwnerProcessID == currentPID) {
			acl_var_main_tid = th32.th32ThreadID;
			break;
		}
	}
}