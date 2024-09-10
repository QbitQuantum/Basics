static int Init(HMODULE hModule)
{
	char szIniPath[MAX_PATH + 16] = { '\0' };
	GetModuleFileNameA(hModule, szIniPath, MAX_PATH);
	char *p = strrchr(szIniPath, '.');
	if (!p)
		return -1;
	p++;
	strcpy(p, "ini");

	HANDLE hFile = CreateFileA(szIniPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return -2;
	CloseHandle(hFile);

	GetPrivateProfileStringA("OPTION", "ADDRESS", "127.0.0.1", g_Host, sizeof(g_Host), szIniPath);
	GetPrivateProfileStringA("OPTION", "PORT", "1192", g_Port, sizeof(g_Port), szIniPath);
	g_SandBoxedRelease = GetPrivateProfileIntA("OPTION", "SANDBOXED_RELEASE", 0, szIniPath);
	g_DisableUnloadBonDriver = GetPrivateProfileIntA("OPTION", "DISABLE_UNLOAD_BONDRIVER", 0, szIniPath);

	g_PacketFifoSize = GetPrivateProfileIntA("SYSTEM", "PACKET_FIFO_SIZE", 64, szIniPath);
	g_TsPacketBufSize = GetPrivateProfileIntA("SYSTEM", "TSPACKET_BUFSIZE", (188 * 1024), szIniPath);

	char szPriority[128];
	GetPrivateProfileStringA("SYSTEM", "PROCESSPRIORITY", "NORMAL", szPriority, sizeof(szPriority), szIniPath);
	if (strcmp(szPriority, "REALTIME") == 0)
		g_ProcessPriority = REALTIME_PRIORITY_CLASS;
	else if (strcmp(szPriority, "HIGH") == 0)
		g_ProcessPriority = HIGH_PRIORITY_CLASS;
	else if (strcmp(szPriority, "ABOVE_NORMAL") == 0)
		g_ProcessPriority = ABOVE_NORMAL_PRIORITY_CLASS;
	else if (strcmp(szPriority, "BELOW_NORMAL") == 0)
		g_ProcessPriority = BELOW_NORMAL_PRIORITY_CLASS;
	else if (strcmp(szPriority, "IDLE") == 0)
		g_ProcessPriority = IDLE_PRIORITY_CLASS;
	else
		g_ProcessPriority = NORMAL_PRIORITY_CLASS;
	SetPriorityClass(GetCurrentProcess(), g_ProcessPriority);

	GetPrivateProfileStringA("SYSTEM", "THREADPRIORITY_TSREADER", "NORMAL", szPriority, sizeof(szPriority), szIniPath);
	if (strcmp(szPriority, "CRITICAL") == 0)
		g_ThreadPriorityTsReader = THREAD_PRIORITY_TIME_CRITICAL;
	else if (strcmp(szPriority, "HIGHEST") == 0)
		g_ThreadPriorityTsReader = THREAD_PRIORITY_HIGHEST;
	else if (strcmp(szPriority, "ABOVE_NORMAL") == 0)
		g_ThreadPriorityTsReader = THREAD_PRIORITY_ABOVE_NORMAL;
	else if (strcmp(szPriority, "BELOW_NORMAL") == 0)
		g_ThreadPriorityTsReader = THREAD_PRIORITY_BELOW_NORMAL;
	else if (strcmp(szPriority, "LOWEST") == 0)
		g_ThreadPriorityTsReader = THREAD_PRIORITY_LOWEST;
	else if (strcmp(szPriority, "IDLE") == 0)
		g_ThreadPriorityTsReader = THREAD_PRIORITY_IDLE;
	else
		g_ThreadPriorityTsReader = THREAD_PRIORITY_NORMAL;

	GetPrivateProfileStringA("SYSTEM", "THREADPRIORITY_SENDER", "NORMAL", szPriority, sizeof(szPriority), szIniPath);
	if (strcmp(szPriority, "CRITICAL") == 0)
		g_ThreadPrioritySender = THREAD_PRIORITY_TIME_CRITICAL;
	else if (strcmp(szPriority, "HIGHEST") == 0)
		g_ThreadPrioritySender = THREAD_PRIORITY_HIGHEST;
	else if (strcmp(szPriority, "ABOVE_NORMAL") == 0)
		g_ThreadPrioritySender = THREAD_PRIORITY_ABOVE_NORMAL;
	else if (strcmp(szPriority, "BELOW_NORMAL") == 0)
		g_ThreadPrioritySender = THREAD_PRIORITY_BELOW_NORMAL;
	else if (strcmp(szPriority, "LOWEST") == 0)
		g_ThreadPrioritySender = THREAD_PRIORITY_LOWEST;
	else if (strcmp(szPriority, "IDLE") == 0)
		g_ThreadPrioritySender = THREAD_PRIORITY_IDLE;
	else
		g_ThreadPrioritySender = THREAD_PRIORITY_NORMAL;

	OSVERSIONINFOEXA osvi = {};
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	osvi.dwMajorVersion = 6;	// >= Vista
	if (VerifyVersionInfoA(&osvi, VER_MAJORVERSION, VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL)))
		g_ThreadExecutionState = ES_SYSTEM_REQUIRED | ES_CONTINUOUS | ES_AWAYMODE_REQUIRED;
	else
		g_ThreadExecutionState = ES_SYSTEM_REQUIRED | ES_CONTINUOUS;

	return 0;
}