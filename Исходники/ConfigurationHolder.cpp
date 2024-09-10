bool ConfigurationHolder::readNumericFromConfigFile(Configuration & configObject, int nBase)
{
	WCHAR buf[21]; // UINT64_MAX in dec has 20 digits
	DWORD read = GetPrivateProfileString(CONFIG_FILE_SECTION_NAME, configObject.getName(), L"", buf, _countof(buf), configPath);

	if (read > 0 && wcslen(buf) > 0)
	{
#ifdef _WIN64
		configObject.setNumeric(_wcstoui64(buf, NULL, nBase));
#else
		configObject.setNumeric(wcstoul(buf, NULL, nBase));
#endif
		return true;
	}

	return false;
}