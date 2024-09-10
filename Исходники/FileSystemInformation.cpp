WString FileTimeToString(const FILETIME& filetime)
{
	SYSTEMTIME localSystemTime;
	FileTimeToSystemTime(&filetime, &localSystemTime);

	// Get the correct locale
	wchar_t localeName[LOCALE_NAME_MAX_LENGTH]={0};
	GetSystemDefaultLocaleName(localeName, sizeof(localeName)/sizeof(*localeName));

	// Get the localized date string
	wchar_t dateString[100]={0};
	GetDateFormatEx(localeName, DATE_SHORTDATE, &localSystemTime, NULL, dateString, sizeof(dateString)/sizeof(*dateString), NULL);

	// Get the localized time string
	wchar_t timeString[100]={0};
	GetTimeFormatEx(localeName, TIME_FORCE24HOURFORMAT | TIME_NOSECONDS, &localSystemTime, NULL, timeString, sizeof(timeString)/sizeof(*timeString));

	return dateString+WString(L" ")+timeString;
}