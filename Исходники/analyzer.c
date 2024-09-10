int execute_apktool(const char* path, const char* args)
{
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	char cmd[MAX_PATH];
	BOOL ret;

	memset(&pi, 0, sizeof(pi));
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	snprintf(cmd, sizeof(cmd), "cmd /C %s %s", path, args);

	ret = CreateProcessA(NULL, cmd, NULL, NULL, TRUE, 
		DETACHED_PROCESS, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return ret ? 0 : 1;
}