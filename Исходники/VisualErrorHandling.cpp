void writeLogW(const wchar_t* const infoStr) {
#if TARGET_OS_MAC
	printf("%ls\n", infoStr);
#endif
#if TARGET_OS_WIN
	HANDLE hSource;
	wchar_t* szList[1];
	szList[0] = const_cast<wchar_t*>(infoStr);
	hSource = RegisterEventSource(NULL, VizKit::VisualConfiguration::kVisualPluginName);
	if (hSource != NULL)  {
		ReportEventW(hSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCWSTR*)szList, NULL);
		DeregisterEventSource(hSource);
	}
#endif
}