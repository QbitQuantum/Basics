//摘要信息
const std::string GetSummary(HANDLE hProcess)
{
	std::string strRet;
	char szTemp[1024] = {0};

	PROCESS_MEMORY_COUNTERS memInfo;
	GetProcessMemoryInfo(hProcess, &memInfo, sizeof(PROCESS_MEMORY_COUNTERS));
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "WorkingSetSize=%.2fM\r\n", (double)memInfo.WorkingSetSize/(1024*1024));
	strRet += szTemp;
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "PagefileUsage=%.2fM\r\n", (double)memInfo.PagefileUsage /(1024*1024));
	strRet += szTemp;

	char szName[1024] = {0};
	DWORD cchName = _countof(szName);
	::GetUserNameA(szName, &cchName);
	szName[cchName] = 0;
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "UserName=%s\r\n", szName);
	strRet += szTemp;

	memset(szName, 0, sizeof(szName));
	cchName = _countof(szName);
	GetComputerNameA(szName, &cchName);
	szName[cchName] = 0;
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "ComputerName=%s\r\n", szName);
	strRet += szTemp;

	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "OSVer=%s\r\n", GetOSVer().c_str());	
	strRet += szTemp;

	SYSTEM_INFO	SystemInfo = {0};
	GetSystemInfo(&SystemInfo);
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "CPU=%d processor(s), type %d arch %d\r\n", SystemInfo.dwNumberOfProcessors, SystemInfo.dwProcessorType, SystemInfo.wProcessorArchitecture);
	strRet += szTemp;
  
  //YYBrowser Begin
  //GlobalMemoryStatus这个api本身就是有bug的。详细:http://msdn.microsoft.com/en-us/library/aa366586(v=vs.85).aspx
  //改为GlobalMemoryStatusEx.add by hzz 2014-10-28 14:43:42
	MEMORYSTATUSEX memoryStatus;
	memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memoryStatus);
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "MemoryLoad=%d\r\n", memoryStatus.dwMemoryLoad);
	strRet += szTemp;
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "TotalPhys=%.2fM\r\n", (double)memoryStatus.ullTotalPhys/(1024*1024));
	strRet += szTemp;
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "AvailPhys=%.2fM\r\n", (double)memoryStatus.ullAvailPhys/(1024*1024));
	strRet += szTemp;
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "TotalVirtual=%.2fM\r\n", (double)memoryStatus.ullTotalVirtual/(1024*1024));
	strRet += szTemp;
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "AvailVirtual=%.2fM\r\n", (double)memoryStatus.ullAvailVirtual/(1024*1024));
	strRet += szTemp;
  //YYBrowser End
	UINT driveType = GetDriveType(NULL);
	_snprintf_s(szTemp, _countof(szTemp), _TRUNCATE, "DriveType=%d\r\n", driveType);
	strRet += szTemp;

	return strRet;
}