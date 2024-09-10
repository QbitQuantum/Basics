	HANDLE WINAPI Hook_OpenMutexA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName)
	{
		if (lpName != nullptr && strcmp(lpName, "report") == 0)
			lpName = mutexName;
		return OpenMutexA(dwDesiredAccess, bInheritHandle, lpName);
	}