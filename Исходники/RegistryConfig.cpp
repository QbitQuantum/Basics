CRegistryConfig::~CRegistryConfig()
{
	if (m_hKey!=NULL) {
		RegCloseKey(m_hKey);
	}
}