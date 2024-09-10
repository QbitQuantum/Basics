void BundleManager::SetDirModDate(wxFileName& path, const wxDateTime& modDate) {
#ifdef __WXMSW__
	wxLogDebug(wxT("SetDirModDate: %s %s"), modDate.FormatDate(), modDate.FormatTime());
	HANDLE hDir = ::CreateFile (
		path.GetPath(),
		GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);

	FILETIME ftWrite;
	ConvertWxToFileTime(&ftWrite, modDate);

	::SetFileTime(hDir, &ftWrite, &ftWrite, &ftWrite);

	::CloseHandle(hDir);
#else
	path.SetTimes(NULL, &modDate, NULL);
#endif
}