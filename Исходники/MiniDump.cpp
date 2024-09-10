BOOL CMiniDump::GetDumpFileName(std::wstring& strDump)
{
	time_t timeExcep;
	TCHAR szTime[64] = {0}, szPath[MAX_PATH] = {0};
	TCHAR *pTmp;


	// 创建dump文件夹
	::GetModuleFileName(NULL, szPath, MAX_PATH * sizeof(TCHAR));
    pTmp = wcschr(szPath, '\\');
	if (pTmp != NULL)
		*pTmp = '\0';
	strDump = pTmp;
	strDump += L"Dump\\";
	CreateDirectory(strDump.c_str(), NULL);


	// 获取时间，组成dump文件名
	timeExcep = time(NULL);
	 wcsftime(szTime, sizeof(szTime), L"%Y%m%d%H%M%S", localtime(&timeExcep));
	 strDump += L"DumpFile_";
	 strDump += szTime;
	 strDump += L"_App";
	 strDump += L".dmp";

	return TRUE;
}