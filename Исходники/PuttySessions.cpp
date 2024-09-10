void PuttySessions::loadRegSessions()
{
	QStringList sessions;
	HKEY key;
	DWORD i, keyname_length;
	TCHAR keyname[256];

	if (RegOpenKeyEx(HKEY_CURRENT_USER, PuttySessions::REG_POS, 0, KEY_ENUMERATE_SUB_KEYS, &key) == ERROR_SUCCESS) {
		keyname_length = sizeof(keyname)/sizeof(TCHAR);
		for (i=0; RegEnumKeyExW(key, i, keyname, &keyname_length, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; ++i) {
			this->append(unmungeString(keyname));
			keyname_length = sizeof(keyname)/sizeof(TCHAR);
		}

		RegCloseKey(key);
	}
}