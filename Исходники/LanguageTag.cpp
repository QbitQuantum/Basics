void LanguageTag::init()
{
#if defined(_WIN32)
#if defined(POCO_WIN32_UTF8)
	wchar_t buffer[8];
	int len = GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SISO639LANGNAME, (LPWSTR) &buffer, sizeof(buffer)/sizeof(wchar_t));
	if (len > 0) Poco::UnicodeConverter::toUTF8(buffer, _primaryTag);
	len = GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, (LPWSTR) &buffer, sizeof(buffer)/sizeof(wchar_t));
	if (len > 0) Poco::UnicodeConverter::toUTF8(buffer, _subTags);
#else
	char buffer[8];
	int len = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SISO639LANGNAME, (LPSTR) &buffer, sizeof(buffer));
	if (len > 0) _primaryTag.assign(buffer);
	len = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, (LPSTR) &buffer, sizeof(buffer));
	if (len > 0) _subTags.assign(buffer);
#endif
#endif

	if (_primaryTag.empty())
	{
		init(Poco::Environment::get("LANG", "en-US"));
	}
}