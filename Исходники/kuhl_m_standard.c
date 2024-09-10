NTSTATUS kuhl_m_standard_version(int argc, wchar_t * argv[])
{
	BOOL isWow64;
	#ifdef _M_X64
	isWow64 = TRUE;
	#else
	if(IsWow64Process(GetCurrentProcess(), &isWow64))
	#endif
	{
		kprintf(
			L"\n" MIMIKATZ L" " MIMIKATZ_VERSION L" (arch " MIMIKATZ_ARCH L")\n"
			L"NT     -  Windows NT %u.%u build %u (arch x%s)\n",
			MIMIKATZ_NT_MAJOR_VERSION, MIMIKATZ_NT_MINOR_VERSION, MIMIKATZ_NT_BUILD_NUMBER, isWow64 ? L"64" : L"86"
			);
	}
	return STATUS_SUCCESS;
}