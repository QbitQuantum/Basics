void cPluginManager::TabCompleteCommand(const AString & a_Text, AStringVector & a_Results, cPlayer * a_Player)
{
	for (CommandMap::iterator itr = m_Commands.begin(), end = m_Commands.end(); itr != end; ++itr)
	{
		if (NoCaseCompare(itr->first.substr(0, a_Text.length()), a_Text) != 0)
		{
			// Command name doesn't match
			continue;
		}
		if ((a_Player != nullptr) && !a_Player->HasPermission(itr->second.m_Permission))
		{
			// Player doesn't have permission for the command
			continue;
		}

		/*  Client expects to only get back the last part of a space separated command.
		Find the position of the beginning of the last part:
		Position of last space + 1 for space separated commands
		string::npos + 1 = 0 for commands that are not separated

		Then skip all commands that have too many subcommands.
		When the client asks for suggestions for "/time s"
		the server must skip all commands that consist of more than 2 words just as
		"/time set day". Or in other words, the position of the last space (separator)
		in the strings must be equal or string::npos for both. */
		size_t LastSpaceInText = a_Text.find_last_of(' ') + 1;
		size_t LastSpaceInSuggestion = itr->first.find_last_of(' ') + 1;

		if (LastSpaceInText != LastSpaceInSuggestion)
		{
			// Suggestion has more subcommands than a_Text
			continue;
		}

		a_Results.push_back(itr->first.substr(LastSpaceInSuggestion));
	}
}