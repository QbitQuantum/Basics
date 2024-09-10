void RegTree::InitPrefixs( void )
{
	HKEY key;
	wstring path;

	RegOpenCurrentUser(KEY_READ, &key);
	ResolveKey(key, path);
	m_currentUserPrefix = path;

	Real_RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Classes", 0, KEY_READ, &key);
	ResolveKey(key, path);
	m_classesRootPrefix = path;

	Real_RegOpenKeyExW(HKEY_CURRENT_CONFIG, L"Software", 0, KEY_READ, &key);
	ResolveKey(key, path);
	m_currentConfigSoftwarePrefix = path;

	Real_RegOpenKeyExW(HKEY_CURRENT_CONFIG, L"System", 0, KEY_READ, &key);
	ResolveKey(key, path);
	m_currentConfigSystemPrefix = path;
}