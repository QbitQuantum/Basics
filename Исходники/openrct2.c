// TODO move to platform
static void openrct2_set_exe_path()
{
#ifdef _WIN32
	wchar_t exePath[MAX_PATH];
	wchar_t tempPath[MAX_PATH];
	wchar_t *exeDelimiter;
	int exeDelimiterIndex;

	GetModuleFileNameW(NULL, exePath, MAX_PATH);
	exeDelimiter = wcsrchr(exePath, platform_get_path_separator());
	exeDelimiterIndex = (int)(exeDelimiter - exePath);
	lstrcpynW(tempPath, exePath, exeDelimiterIndex + 1);
	tempPath[exeDelimiterIndex] = L'\0';
	_wfullpath(exePath, tempPath, MAX_PATH);
	WideCharToMultiByte(CP_UTF8, 0, exePath, countof(exePath), gExePath, countof(gExePath), NULL, NULL);
#else
	char exePath[MAX_PATH];
	ssize_t bytesRead;
	bytesRead = readlink("/proc/self/exe", exePath, MAX_PATH);
	if (bytesRead == -1) {
		log_fatal("failed to read /proc/self/exe");
	}
	exePath[bytesRead] = '\0';
	log_verbose("######################################## Setting exe path to %s", exePath);
	char *exeDelimiter = strrchr(exePath, platform_get_path_separator());
	if (exeDelimiter == NULL)
	{
		log_error("should never happen here");
		gExePath[0] = '\0';
		return;
	}
	int exeDelimiterIndex = (int)(exeDelimiter - exePath);

	safe_strncpy(gExePath, exePath, exeDelimiterIndex + 1);
	gExePath[exeDelimiterIndex] = '\0';
#endif // _WIN32
}