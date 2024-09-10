int _tmain(int argc, _TCHAR *argv[])
{
	_wsetlocale(LC_ALL, L"korean");

	//if (argc != 3)
	//{
	//	wprintf(L"usage : %s <pid> <dll_path>", argv[0]);
	//	return -1;
	//}

	argv[1] = L"11424";
	argv[2] = L"stealth.dll";

	char *szDllName;
	int strSize = WideCharToMultiByte(CP_ACP, 0, argv[2], -1, NULL, 0, NULL, NULL);
	szDllName = new char[strSize];
	WideCharToMultiByte(CP_ACP, 0, argv[2], -1, szDllName, strSize, 0, 0);

	DWORD pid;
	TCHAR *pEnd;
	pid = wcstol(argv[1], &pEnd, 10);

	if (injection(pid, szDllName) == FALSE)
	{
		errorLOG("injection()");
		return -1;
	}

	return 0;
}