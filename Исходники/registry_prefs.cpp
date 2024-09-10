template<> bool read_registry_pref(const std::string& pref_key, std::string& value) {
	HKEY hKey = 0;

	CHAR data[512];
	DWORD cbData = sizeof(data);

	if (RegCreateKeyA(HKEY_LOCAL_MACHINE, heroes2RegistrySubKey, &hKey) != ERROR_SUCCESS) {
		return false;
	}

	if (RegQueryValueExA(hKey, pref_key.c_str(), 0, NULL, (LPBYTE)data, &cbData) != ERROR_SUCCESS) {
		return false;
	}

	std::string sdata(data);
	value = sdata;
	return true;
}