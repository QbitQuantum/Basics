HANDLE open_app_map(const wchar_t *sid, const wchar_t *name)
{
	wchar_t path[MAX_PATH];
	DWORD session_id = WTSGetActiveConsoleSessionId();
	_snwprintf(path, MAX_PATH, path_format, session_id, sid, name);
	return nt_open_map(path);
}