bool ProxyClient::ProcessStringCmd(char *string)
{
	if (BaseClient::ProcessStringCmd(string)) {
		return true;
	}

	TokenLine cmdLine;
	if (!cmdLine.SetLine(string)) {
		m_System->Printf("WARNING! ProxyClient::ProcessStringCmd: string command too long.\n");
		return true;
	}

	char *cmd = cmdLine.GetToken(0);
	for (auto& local_cmd : m_LocalCmdReg)
	{
		if (!_stricmp(local_cmd.name, cmd)) {
			(this->*local_cmd.pfnCmd)(&cmdLine);
			return true;
		}
	}

	if (m_ClientType < TYPE_COMMENTATOR) {
		m_System->DPrintf("Unkown client command: \"%s\"\n", cmd);
	}

	m_System->DPrintf("Unkown director command: \"%s\"\n", cmd);
	return false;
}