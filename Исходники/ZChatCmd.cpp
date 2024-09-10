void ZChatCmdManager::AddAlias(const char* szNewCmdName, const char* szTarCmdName)
{
/*
	ZChatCmd* pCmd = GetCommandByName(szTarCmdName);
	if (pCmd == NULL)
	{
		_ASSERT(0);		// 앨리어스 대상 커맨드가 존재하지 않음
		return;
	}
*/

	char szLwrName[256];
	strcpy(szLwrName, szNewCmdName);
	_strlwr(szLwrName);

	m_AliasMap.insert(map<std::string, std::string>::value_type(std::string(szLwrName), std::string(szTarCmdName)));
}