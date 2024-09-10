//Returns true on success (and sets majorVersion and minorVersion). Returns false on failure.
bool GetOSVersion(DWORD* majorVersion, DWORD* minorVersion)
{
	bool success = false;

	if (IsWindowsVistaOrGreater())
	{
		success = true;
		*majorVersion = 6;
		*minorVersion = 0;
	}
	if (IsWindows7OrGreater())
	{
		*minorVersion = 1;
	}
	if (IsWindows8OrGreater())
	{
		*minorVersion = 2;
	}
	if (IsWindows8Point1OrGreater())
	{
		*minorVersion = 3;
	}

	return success;
}