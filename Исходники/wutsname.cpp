int uname(struct utsname* un)
{
	OSVERSIONINFOW vi = { sizeof(OSVERSIONINFOW) };
	GetVersionExW(&vi);

	// OS implementation name
	sprintf_s(un->sysname, ARRAY_SIZE(un->sysname), "%ls", wversion_Family());

	// release info
	const wchar_t* vs = vi.szCSDVersion;
	int sp;
	if(swscanf_s(vs, L"Service Pack %d", &sp) == 1)
		sprintf_s(un->release, ARRAY_SIZE(un->release), "SP %d", sp);
	else
		un->release[0] = '\0';

	// version
	sprintf_s(un->version, ARRAY_SIZE(un->version), "%ls.%lu", wversion_String(), vi.dwBuildNumber & 0xFFFF);

	// node name
	{
		WinScopedPreserveLastError s;	// GetComputerName
		DWORD bufSize = sizeof(un->nodename);
		WARN_IF_FALSE(GetComputerNameA(un->nodename, &bufSize));
	}

	// hardware type
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	if(si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
		strcpy_s(un->machine, ARRAY_SIZE(un->machine), "x64");
	else
		strcpy_s(un->machine, ARRAY_SIZE(un->machine), "x86");

	return 0;
}