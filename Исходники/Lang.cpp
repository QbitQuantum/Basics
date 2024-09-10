std::wstring LanguageSetting::GetLanguageW(TCHAR *key, TCHAR *name) {
	TCHAR str[255];
	GetPrivateProfileStringW(key, name, L"", str, 255, L".\\lang.ini");
	if (wcslen(str) == 0) {
		swprintf(str, L"Error: No Language keyname \"%s\" in Key \"%s\".", key, name);
	}

	return replaceAll(std::wstring(str), L"\\n", L"\n");
}