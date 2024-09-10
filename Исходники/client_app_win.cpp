CefString ClientApp::GetCurrentLanguage()
{
	// Get the user's selected language
	// Defaults to the system installed language if not using MUI.
	LANGID langID = GetUserDefaultUILanguage();

	// Convert LANGID to a RFC 4646 language tag (per navigator.language)
	int langSize = GetLocaleInfo(langID, LOCALE_SISO639LANGNAME, NULL, 0);
	int countrySize = GetLocaleInfo(langID, LOCALE_SISO3166CTRYNAME, NULL, 0);

	wchar_t *lang = new wchar_t[langSize + countrySize + 1];
	wchar_t *country = new wchar_t[countrySize];
	
	GetLocaleInfo(langID, LOCALE_SISO639LANGNAME, lang, langSize);
	GetLocaleInfo(langID, LOCALE_SISO3166CTRYNAME, country, countrySize);

	// add hyphen
	wcscat(wcscat(lang, L"-"), country);
	std::wstring locale(lang);

	delete [] lang;
	delete [] country;

	return CefString(locale);
}