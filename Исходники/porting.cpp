std::string get_sysinfo()
{
#ifdef _WIN32

	std::ostringstream oss;
	LPSTR filePath = new char[MAX_PATH];
	UINT blockSize;
	VS_FIXEDFILEINFO *fixedFileInfo;

	GetSystemDirectoryA(filePath, MAX_PATH);
	PathAppendA(filePath, "kernel32.dll");

	DWORD dwVersionSize = GetFileVersionInfoSizeA(filePath, NULL);
	LPBYTE lpVersionInfo = new BYTE[dwVersionSize];

	GetFileVersionInfoA(filePath, 0, dwVersionSize, lpVersionInfo);
	VerQueryValueA(lpVersionInfo, "\\", (LPVOID *)&fixedFileInfo, &blockSize);

	oss << "Windows/"
		<< HIWORD(fixedFileInfo->dwProductVersionMS) << '.' // Major
		<< LOWORD(fixedFileInfo->dwProductVersionMS) << '.' // Minor
		<< HIWORD(fixedFileInfo->dwProductVersionLS) << ' '; // Build

	#ifdef _WIN64
	oss << "x86_64";
	#else
	BOOL is64 = FALSE;
	if (IsWow64Process(GetCurrentProcess(), &is64) && is64)
		oss << "x86_64"; // 32-bit app on 64-bit OS
	else
		oss << "x86";
	#endif

	delete[] lpVersionInfo;
	delete[] filePath;

	return oss.str();
#else
	struct utsname osinfo;
	uname(&osinfo);
	return std::string(osinfo.sysname) + "/"
		+ osinfo.release + " " + osinfo.machine;
#endif
}