DWORD IATHookInjector::FindRemotePEB(HANDLE hProcess) const
{
	auto hNTDLL = LoadLibraryA("ntdll");
	if (!hNTDLL)
	{
		return 0;
	}
	auto fpNtQueryInformationProcess = GetProcAddress(hNTDLL, "NtQueryInformationProcess");
	if (!fpNtQueryInformationProcess)
	{
		return 0;
	}
	auto ntQueryInformationProcess = NtQueryInformationProcess(fpNtQueryInformationProcess);
	auto pBasicInfo = new PROCESS_BASIC_INFORMATION();
	DWORD dwReturnLength = 0;
	ntQueryInformationProcess(hProcess, 0, pBasicInfo, sizeof(PROCESS_BASIC_INFORMATION), &dwReturnLength);
	return DWORD(pBasicInfo->PebBaseAddress);
}