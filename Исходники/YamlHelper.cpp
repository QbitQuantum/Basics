UINT64 YamlLoadHelper::LoadUint64(const std::string key)
{
	bool bFound;
	std::string value = m_yamlHelper.GetMapValue(*m_pMapYaml, key, bFound);
	if (value == "")
	{
		m_bDoGetMapRemainder = false;
		throw std::string(m_currentMapName + ": Missing: " + key);
	}
	return _strtoui64(value.c_str(), NULL, 0);
}