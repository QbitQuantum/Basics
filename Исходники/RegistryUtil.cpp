bool RegistryUtil::writeString(const std::string& key, const std::string& value, const std::string& data) {
	size_t pos = key.find('\\', 0);
	if (pos == std::string::npos) {
		return false;
	}

	HKEY hkey = getRootKeyFromString(key.c_str(), pos);

	if (hkey == NULL) {
		return false;
	}

	HKEY openKey;
	int32 result = RegOpenKeyExA(hkey, (key.c_str() + pos + 1), 0, KEY_WRITE, &openKey);
	ASSERT(result == ERROR_SUCCESS || result == ERROR_FILE_NOT_FOUND);

	if (result == ERROR_SUCCESS) {
		result = RegSetValueExA(openKey, value.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(data.c_str()), ((int)data.size() + 1));				
		ASSERT(result == ERROR_SUCCESS);

		RegCloseKey(openKey);
	}
	return (result == ERROR_SUCCESS);
}