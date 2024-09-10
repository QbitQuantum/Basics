const TCHAR *PerfCounterMuninNodePlugin::GetPdhCounterEnglishName(const TCHAR *localName)
{
	DWORD status;
	DWORD fIndex;
	status = PdhLookupPerfIndexByNameW(NULL, localName, &fIndex);
	if (status == ERROR_SUCCESS && englishCounterNames.count(fIndex) > 0) {
		return englishCounterNames.at(fIndex).c_str();
	}
	return localName;
}