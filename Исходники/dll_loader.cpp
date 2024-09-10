int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	LPWSTR dllName = 0;
	LPWSTR appName = 0;
	LPWSTR appArg = 0;
	int argc = 0;
	LPWSTR *argv = CommandLineToArgvW(lpCmdLine, &argc);
	for (int i = 0; i < argc; i++) {
		if (!_wcsicmp(L"--dll", argv[i])) {
			i++;
			dllName = argv[i];
		} else if (!_wcsicmp(L"--app", argv[i])) {
			i++;
			appName = argv[i];
		} else if (!_wcsicmp(L"--arg", argv[i])) {
			i++;
			appArg = argv[i];
		} else if (!_wcsicmp(L"--help", argv[i])) {

			MessageBox(NULL, L"DllLoader.exe --dll test.dll --app target.exe --arg \"arg0=123\"", L"Help", 0);

			return 0;
		}
	}

	if (!dllName || !appName) {
		MessageBox(NULL, L"--dll and --app can't be empty", L"", 0);
		return 1;
	}

	wchar_t appPath[1024];
	wchar_t envPath[512];
	wchar_t dllPath[512];

	GetModuleFileName(NULL, envPath, sizeof(envPath) / sizeof(envPath[0]));
	memcpy(appPath, envPath, sizeof(envPath));
	memcpy(dllPath, envPath, sizeof(envPath));

	wchar_t *e = wcsrchr(envPath, L'\\');
	e[0] = 0x00;
	wcscpy(e + 1 - envPath + dllPath, dllName);
	if (appArg)
		swprintf(e + 1 - envPath + appPath, 512, L"%s %s", appName, appArg);
	else
		wcscpy(e + 1 - envPath + appPath, appName);

	STARTUPINFOW si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcess(NULL, appPath, 0, 0, 0, CREATE_SUSPENDED, 0, envPath, &si, &pi)) {
		MessageBox(NULL, L"can't create process!", L"", 0);
		return 1;
	}

	LPVOID libArg = VirtualAllocEx(pi.hProcess, 0, sizeof(dllPath), MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(pi.hProcess, libArg, dllPath, sizeof(dllPath), 0);

	QueueUserAPC((PAPCFUNC)&LoadLibrary, pi.hThread, (ULONG_PTR)libArg);

	ResumeThread(pi.hThread);
	CloseHandle(pi.hThread);
	LocalFree(argv);

	//WaitForSingleObject(pi.hProcess, -1);
	CloseHandle(pi.hProcess);

	return 0;
}