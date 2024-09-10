/////////////////////////////////////////////////////////////////////
// GetMemoryInfo => 메모리에 대한 정보를 얻어온다. (단위 MB)
// dwTotalMemMB : 시스템 전체 메모리 용량
// dwAvailMemMB : 사용중인 메모리 용량
// dwVirtualMemMB : 가상메모리 전체 용량
/////////////////////////////////////////////////////////////////////
void MBMatchSystemInfo::GetMemoryInfo(DWORD* dwTotalMemMB, DWORD* dwAvailMemMB, DWORD* dwVirtualMemMB)
{
#ifdef _MONITORING
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	DWORDLONG lMemTotalMB = (statex.ullTotalPhys / (1024 * 1024));
	*dwTotalMemMB = (DWORD)lMemTotalMB;

	DWORDLONG lAvailMemMB = (statex.ullAvailPhys / (1024 * 1024));
	*dwAvailMemMB = (DWORD)lAvailMemMB;

	DWORDLONG lVirtualMemMB = (statex.ullTotalVirtual / (1024 * 1024));
	*dwVirtualMemMB = (DWORD)lVirtualMemMB;
#endif
}