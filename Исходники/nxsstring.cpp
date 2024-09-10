void NxsString::add_nxs_quotes(std::string &s)
	{
	std::string withQuotes;
	unsigned len = (unsigned)s.length();
	withQuotes.reserve(len + 4);
	withQuotes.append(1,'\'');
	for (std::string::const_iterator sIt = s.begin(); sIt != s.end(); sIt++)
		{
		withQuotes.append(1, *sIt);
		if (*sIt == '\'')
			withQuotes.append(1,'\'');
		}
	withQuotes.append(1,'\'');
	s.swap(withQuotes);
	}