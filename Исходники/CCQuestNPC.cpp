CCQuestNPCSetInfo* CCQuestNPCSetCatalogue::GetInfo(const char* szName)
{
	char szLwrName[64];
	strcpy(szLwrName, szName);
	string strName = _strlwr(szLwrName);

	map<string, CCQuestNPCSetInfo*>::iterator itor = m_NameMap.find(strName);
	if (itor != m_NameMap.end())
	{
		return (*itor).second;
	}

	_ASSERT(0);
	return NULL;
}