/*函数实现*/
BOOL WINAPI CrashProc(PEXCEPTION_POINTERS Exception)
{   
	// 获取当前进程所在路径
	wchar_t *pFindPath = NULL;
	wchar_t wsModeleBaseName[256] = L"";
	wchar_t wsCrashXmlFileName[256] = L"";
	wchar_t wsCrashDumpFileName[256] = L"";
	wchar_t wsModeleReverseName[256] = L"";
	GetModuleFileNameEx(GetCurrentProcess(), NULL, wsModeleBaseName, sizeof(wsModeleBaseName));
	wcscpy(wsModeleReverseName, wcsrev(wsModeleBaseName));
	for (INT16 _i = 0; _i < 256; _i++)
	{
		if (wsModeleReverseName[_i] == 0)
			break;
		if (wsModeleReverseName[_i] == L'/')
			wsModeleReverseName[_i] = L'\\';
	}
	pFindPath = wcsstr(wsModeleReverseName, L"\\");
	wcscpy(wsModeleBaseName, wcsrev(pFindPath));
	wcscat(wsModeleBaseName, L"CrashRpt\\");

	// 创建对应文件目录
	SYSTEMTIME st;
	wchar_t wsDatePath[256];
	memset(&st, 0, sizeof(SYSTEMTIME));
	GetLocalTime(&st);
	wsprintf(wsDatePath, L"%s%04d-%02d-%02d\\", wsModeleBaseName, st.wYear, st.wMonth, st.wDay);
	CreateDirectory(wsModeleBaseName, NULL);
	CreateDirectory(wsDatePath, NULL);

	// 生成文件路径
	wsprintf(wsCrashXmlFileName, L"%sCrashRpt_%02d%02d%02d.xml", wsDatePath, st.wHour, st.wMinute, st.wSecond);
	wsprintf(wsCrashDumpFileName, L"%sCrashRpt_%02d%02d%02d.dmp", wsDatePath, st.wHour, st.wMinute, st.wSecond);

	//生成错误时系统快照
	GenerateCrashRpt(Exception, wsCrashXmlFileName, CRASHRPT_ERROR|CRASHRPT_SYSTEM|CRASHRPT_PROCESS|CRASHRPT_SOFTWARE|CRASHRPT_HARDWARE);

	//生成minidump.dmp，这个可以用vc或者windbg打开分析
	GenerateMiniDump(Exception, wsCrashDumpFileName);

	return EXCEPTION_EXECUTE_HANDLER;
}