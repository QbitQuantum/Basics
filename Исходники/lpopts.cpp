static void DisplayPackInfo(HWND hwndDlg, const LANGPACK_INFO *pack)
{
	/* locale string */
	if (!(pack->flags & LPF_NOLOCALE)) {
		TCHAR szLocaleName[256], szLanguageName[128], szContryName[128];

		if (!GetLocaleInfo(pack->Locale, WINVER >= _WIN32_WINNT_WIN7 ? LOCALE_SENGLISHLANGUAGENAME : LOCALE_SENGLANGUAGE, szLanguageName, _countof(szLanguageName)))
			szLanguageName[0] = _T('\0');
		if (!GetLocaleInfo(pack->Locale, WINVER >= _WIN32_WINNT_WIN7 ? LOCALE_SENGLISHCOUNTRYNAME : LOCALE_SENGCOUNTRY, szContryName, _countof(szContryName)))
			szContryName[0] = _T('\0');
		
		/* add some note if its incompatible */
		if (szLanguageName[0] && szContryName[0]) {
			mir_sntprintf(szLocaleName, _T("%s (%s)"), TranslateTS(szLanguageName), TranslateTS(szContryName));
			if (!IsValidLocale(pack->Locale, LCID_INSTALLED)) {
				TCHAR *pszIncompat;
				pszIncompat = TranslateT("(incompatible)");
				szLocaleName[_countof(szLocaleName) - mir_tstrlen(pszIncompat) - 1] = 0;
				mir_tstrcat(mir_tstrcat(szLocaleName, _T(" ")), pszIncompat);
			}
			SetDlgItemText(hwndDlg, IDC_LANGLOCALE, szLocaleName);
		}
		else SetDlgItemText(hwndDlg, IDC_LANGLOCALE, TranslateT("Unknown"));
	}
	else SetDlgItemText(hwndDlg, IDC_LANGLOCALE, TranslateT("Unknown"));
	
	/* file date */
	SYSTEMTIME stFileDate;
	TCHAR szDate[128]; szDate[0] = 0;
	if (FileTimeToSystemTime(&pack->ftFileDate, &stFileDate))
		GetDateFormat(Langpack_GetDefaultLocale(), DATE_SHORTDATE, &stFileDate, NULL, szDate, _countof(szDate));
	SetDlgItemText(hwndDlg, IDC_LANGDATE, szDate);
	
	/* general */
	SetDlgItemText_CP(hwndDlg, IDC_LANGMODUSING, pack->szLastModifiedUsing);
	SetDlgItemText_CP(hwndDlg, IDC_LANGAUTHORS, pack->szAuthors);
	SetDlgItemText_CP(hwndDlg, IDC_LANGEMAIL, pack->szAuthorEmail);
	SetDlgItemText(hwndDlg, IDC_LANGINFOFRAME, TranslateTS(pack->tszLanguage));
}