char *TemplateHTMLBuilder::timestampToString(DWORD dwFlags, time_t check, int mode)
{
	static char szResult[512];
	TCHAR str[300];
	DBTIMETOSTRINGT dbtts;
	dbtts.cbDest = 70;
	dbtts.szDest = str;
	szResult[0] = '\0';
	if (mode) { //time
		dbtts.szFormat = (dwFlags & Options::LOG_SHOW_SECONDS) ? _T("s") : _T("t");
		CallService(MS_DB_TIME_TIMESTAMPTOSTRINGT, check, (LPARAM)&dbtts);
	}
	else {//date
		struct tm tm_now, tm_today;
		time_t now = time(NULL);
		time_t today;
		tm_now = *localtime(&now);
		tm_today = tm_now;
		tm_today.tm_hour = tm_today.tm_min = tm_today.tm_sec = 0;
		today = mktime(&tm_today);
		if (dwFlags & Options::LOG_RELATIVE_DATE && check >= today)
			_tcsncpy(str, TranslateT("Today"), SIZEOF(str));
		else if(dwFlags & Options::LOG_RELATIVE_DATE && check > (today - 86400))
			_tcsncpy(str, TranslateT("Yesterday"), SIZEOF(str));
		else {
			dbtts.szFormat = (dwFlags & Options::LOG_LONG_DATE) ? _T("D") : _T("d");
			CallService(MS_DB_TIME_TIMESTAMPTOSTRINGT, check, (LPARAM) & dbtts);
		}
	}

	lstrcpynA(szResult, ptrA(mir_utf8encodeT(str)), 500);
	return szResult;
}