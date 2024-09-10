void HtmlDocument::parseHead(void)
{
	char *pBodyStart = strstr(m_pData, "<body");
	if (pBodyStart == NULL)
	{
		pBodyStart = strstr(m_pData, "<BODY");
	}
	if (pBodyStart != NULL)
	{
		string htmlHead(m_pData, pBodyStart - m_pData);
		regex_t titleRegex, httpEquivRegex;
		regmatch_t pTitleMatches[3];
		regmatch_t pHttpEquivMatches[3];
		int titleMatches = 3, httpEquivMatches = 3;

		// Look for a title
		if (regcomp(&titleRegex, "<title([^>]*)>([^<>]*)</title", REG_EXTENDED|REG_ICASE) == 0)
		{
			if ((regexec(&titleRegex, htmlHead.c_str(), titleMatches,
					pTitleMatches, REG_NOTBOL|REG_NOTEOL) == 0) &&
				(pTitleMatches[titleMatches - 1].rm_so != -1))
			{
				string title = htmlHead.substr(pTitleMatches[2].rm_so,
					pTitleMatches[2].rm_eo - pTitleMatches[2].rm_so);

				if (title.empty() == false)
				{
					// Override the title
					m_title = title;
				}
			}
		}
		// ...and a Content-Type
		if (regcomp(&httpEquivRegex, "<meta http-equiv=([^>]*) content=([^>]*)>", REG_EXTENDED|REG_ICASE) == 0)
		{
			if ((regexec(&httpEquivRegex, htmlHead.c_str(), httpEquivMatches,
					pHttpEquivMatches, REG_NOTBOL|REG_NOTEOL) == 0) &&
				(pHttpEquivMatches[httpEquivMatches - 1].rm_so != -1))
			{
				string name = StringManip::removeQuotes(
					htmlHead.substr(pHttpEquivMatches[1].rm_so,
					pHttpEquivMatches[1].rm_eo - pHttpEquivMatches[1].rm_so));
				string content = StringManip::removeQuotes(
					htmlHead.substr(pHttpEquivMatches[2].rm_so,
					pHttpEquivMatches[2].rm_eo - pHttpEquivMatches[2].rm_so));

				if ((content.empty() == false) &&
					(strncasecmp(name.c_str(), "Content-Type",
						min((int)name.length(), 12)) == 0))
				{
					// Override the type
					m_type = content;
				}
			}
		}
#ifdef DEBUG
		cout << "HtmlDocument::parseHead: extracted title " << m_title <<
			", type " << m_type << endl;
#endif

		regfree(&titleRegex);
		regfree(&httpEquivRegex);
	}
}