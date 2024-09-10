void MakeUrlHex(LPTSTR url, LPCTSTR tid)
{
	ULARGE_INTEGER iTid; iTid.QuadPart = _tstoi64(tid);
	LPTSTR tidInUrl = _tcsstr(url, tid);
	LPTSTR trail = tidInUrl + mir_tstrlen(tid);
	wsprintf(tidInUrl, _T("%x%08x"), iTid.HighPart, iTid.LowPart); //!!!!!!!!!!!!
	wmemmove(tidInUrl + mir_tstrlen(tidInUrl), trail, mir_tstrlen(trail) + 1);
}