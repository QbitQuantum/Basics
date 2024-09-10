WORD	MTime::DateFormatAlt(LPTSTR ptszTimeFormat, WORD cchTimeFormat)
{
	if (!ptszTimeFormat || !cchTimeFormat)
		return 0;

	WORD wRes = DateFormat(ptszTimeFormat, cchTimeFormat);
	if (wRes != 0)
		return wRes;

	SYSTEMTIME AltSysTime = _SysTime;
	MTime mtNow;
	mtNow.GetLocalTime();
	AltSysTime.wYear=mtNow.Year();

	if ((cchTimeFormat = GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &AltSysTime, NULL, ptszTimeFormat, cchTimeFormat)) == 0) {
		*ptszTimeFormat = 0;
		return 0;
	}
	
	TCHAR tszText[10];
	_itot(mtNow.Year(), tszText, 10);
	TCHAR * tszYear = _tcsstr(ptszTimeFormat, tszText);

	if (tszYear && mir_tstrlen(tszYear) == 4)
		mir_tstrcpy(tszYear, _T("????"));
	else {
		*ptszTimeFormat = 0;
		return 0;
	}
	
	return cchTimeFormat;
}