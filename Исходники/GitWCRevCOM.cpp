//
// Get a readable string from a __time64_t date
//
BOOL GitWCRev::CopyDateToString(WCHAR* destbuf, int buflen, __time64_t ttime)
{
	const int min_buflen = 32;
	if (!destbuf || (min_buflen > buflen))
		return FALSE;

	struct tm newtime;
	if (_localtime64_s(&newtime, &ttime))
		return FALSE;
	// Format the date/time in international format as yyyy/mm/dd hh:mm:ss
	swprintf_s(destbuf, min_buflen, L"%04d/%02d/%02d %02d:%02d:%02d", newtime.tm_year + 1900, newtime.tm_mon + 1, newtime.tm_mday, newtime.tm_hour, newtime.tm_min, newtime.tm_sec);
	return TRUE;
}