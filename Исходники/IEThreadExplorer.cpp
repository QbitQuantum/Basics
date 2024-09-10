bool isHtmlPage(IHTMLDocument2* doc) 
{
	CComBSTR type;
	if (!SUCCEEDED(doc->get_mimeType(&type))) 
	{
		return false;
	}

	if (!SUCCEEDED(type.ToLower())) 
	{
		return false;
	}

	return wcsstr(combstr2cw(type), L"html") != NULL;
}