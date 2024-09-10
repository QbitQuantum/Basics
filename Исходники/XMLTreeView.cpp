void XmlTreeView::PostProcessSummary(tstring& str)
{
	// Replace empty strings.
	if (str.empty())
	{
		str = TXT("(empty)");
		return;
	}

	bool bWhitespaceOnly = true;

	// Find if only whitespace characters.
	for (tstring::const_iterator it = str.begin(); ((it != str.end()) && bWhitespaceOnly); ++it)
	{
		if (!tisspace(static_cast<utchar>(*it)))
			bWhitespaceOnly = false;
	}

	// Replace "invisible" strings.
	if (bWhitespaceOnly)
	{
		str = TXT("(whitespace)");
		return;
	}

	// Trim string.
	if (str.length() > App.m_nDefMaxItemLen)
	{
		str.erase(App.m_nDefMaxItemLen, str.length()-App.m_nDefMaxItemLen);

		str += TXT("...");
	}
}