void SetThreadName(LPCSTR szThreadName) {
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = szThreadName;
	info.dwThreadID = -1;
	info.dwFlags = 0;
	__try {
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(DWORD), (ULONG_PTR *)&info);
	}
	__except (EXCEPTION_CONTINUE_EXECUTION) {}
}