void DoTasks()
{
	HMODULE hModule;
	FARPROC targetFunction;

	//We can't determine exactly which runtime they use so try em all
	hModule = GetModuleHandle(L"MSVCR100.dll");
	if (hModule == NULL)
		hModule = GetModuleHandle(L"MSVCR110.dll");
	if (hModule == NULL)
		hModule = GetModuleHandle(L"MSVCR120.dll");

	if (hModule ==NULL)
		MessageBox(NULL, L"Failed to Find MSVCR For CT String Crypt", L"Compile Time String XOR Failed", MB_OK);

	//Get Project Directory
	_wgetcwd(WorkingDirectory, MAX_PATH);
	std::wstringstream ssTempDirPath;
	ssTempDirPath << WorkingDirectory << L"\\Temp";
	if (!DirectoryExists(ssTempDirPath.str().c_str()))
	{
		CreateDirectory(ssTempDirPath.str().c_str(), NULL);
	}

	targetFunction = GetProcAddress(hModule, "_wsopen_s");
	owsopen_s = (twsopen_s)DetourFunction((PBYTE)targetFunction, (PBYTE)hkwsopen_s);
}