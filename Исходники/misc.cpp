wxString HtmlEntities(const wxString &str)
{
	wxString ret;

	for (unsigned int x = 0; x < str.Length(); x++)
	{
		if (str[x] != 13)
			ret += GetHtmlEntity(str[x]);
	}

	return ret;
}