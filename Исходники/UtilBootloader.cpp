bool RestartAsNormal(const char* args)
{
	wchar_t name[255];
	GetModuleFileNameW(NULL, name, 255);

	wchar_t szWorkingDir[255];
	GetModuleFileNameW(NULL, szWorkingDir, 255);

	size_t exePathLen = wcsnlen_s(szWorkingDir, 255);
	for (size_t x=exePathLen; x>0; x--)
	{
		if (szWorkingDir[x] == L'\\')
			break;
		else
			szWorkingDir[x] = L'\0';
	}

	wchar_t wArgs[255];
	wArgs[0] = 0;

	if (args)
	{
		for (size_t x=0; x<strlen(args); x++)
			wArgs[x] = (wchar_t)args[x];

		wArgs[strlen(args)] = 0;
	}

	HRESULT res = CreateProcessWithExplorerIL(name, wArgs, szWorkingDir);
	return SUCCEEDED(res);
}