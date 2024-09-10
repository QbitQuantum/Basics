bool WinRegistryKey::exists(const std::string& name)
{
	bool exists = false;
	HKEY hKey;
#if defined(POCO_WIN32_UTF8)
	std::wstring usubKey;
	Poco::UnicodeConverter::toUTF16(_subKey, usubKey);
	if (RegOpenKeyExW(_hRootKey, usubKey.c_str(), 0, KEY_READ | _extraSam, &hKey) == ERROR_SUCCESS)
	{
		std::wstring uname;
		Poco::UnicodeConverter::toUTF16(name, uname);
		exists = RegQueryValueExW(hKey, uname.c_str(), NULL, NULL, NULL, NULL) == ERROR_SUCCESS;
		RegCloseKey(hKey);
	}
#else
	if (RegOpenKeyExA(_hRootKey, _subKey.c_str(), 0, KEY_READ | _extraSam, &hKey) == ERROR_SUCCESS)
	{
		exists = RegQueryValueExA(hKey, name.c_str(), NULL, NULL, NULL, NULL) == ERROR_SUCCESS;
		RegCloseKey(hKey);
	}
#endif
	return exists;
}