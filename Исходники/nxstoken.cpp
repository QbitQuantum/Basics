std::map<std::string, std::string> NxsToken::ParseAsSimpleKeyValuePairs(const ProcessedNxsCommand & tv, const char *cmdName)
	{
	std::map<std::string, std::string> kv;
	std::string key;
	ProcessedNxsCommand::const_iterator tvIt = tv.begin();
	ProcessedNxsCommand::const_iterator prevIt;
	ProcessedNxsCommand::const_iterator endIt = tv.end();
	while (tvIt != endIt)
		{
		key = tvIt->GetToken().c_str();
		prevIt = tvIt++;
		if (tvIt == endIt || tvIt->GetToken() != "=")
			{
			NxsString m("Expecting = after ");
			m += key.c_str();
			m += " in ";
			m += cmdName;
			m += " command.";
			if (tvIt == endIt)
				throw NxsException(m, prevIt->GetFilePosition(), prevIt->GetLineNumber(), prevIt->GetColumnNumber());
			else
				throw NxsException(m, tvIt->GetFilePosition(), tvIt->GetLineNumber(), tvIt->GetColumnNumber());
			}
		prevIt = tvIt++;
		if (tvIt == endIt)
			{
			NxsString m("Expecting a value after = in the  ");
			m += key.c_str();
			m += " subcommand of the in ";
			m += cmdName;
			m += " command.";
			throw NxsException(m, prevIt->GetFilePosition(), prevIt->GetLineNumber(), prevIt->GetColumnNumber());
			}
		kv[key] = tvIt->GetToken();
		tvIt++;
		}
	return kv;
	}