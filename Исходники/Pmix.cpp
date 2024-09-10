void ConvertDate(const FILETIME& ft,wchar_t *DateText,wchar_t *TimeText)
{
	if (ft.dwHighDateTime==0 && ft.dwLowDateTime==0)
	{
		if (DateText!=NULL)
			*DateText=0;

		if (TimeText!=NULL)
			*TimeText=0;

		return;
	}

	SYSTEMTIME st;
	FILETIME ct;
	FileTimeToLocalFileTime(&ft,&ct);
	FileTimeToSystemTime(&ct,&st);

	if (TimeText!=NULL)
		GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, 0, TimeText, MAX_DATETIME);

	if (DateText!=NULL)
		GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, 0, DateText, MAX_DATETIME);
}