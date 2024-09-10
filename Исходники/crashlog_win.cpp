/* virtual */ char *CrashLogWindows::LogOSVersion(char *buffer, const char *last) const
{
	_OSVERSIONINFOA os;
	os.dwOSVersionInfoSize = sizeof(os);
	GetVersionExA(&os);

	return buffer + seprintf(buffer, last,
			"Operating system:\n"
			" Name:     Windows\n"
			" Release:  %d.%d.%d (%s)\n",
			(int)os.dwMajorVersion,
			(int)os.dwMinorVersion,
			(int)os.dwBuildNumber,
			os.szCSDVersion
	);

}