void ConfigurationRemoteXmlParser::ParseBlockCompatibility(XmlNode node)
{
	if (node.GetName().compare(L"version")==0)
	{
		m_configuration.SetCompatibility(node.GetText());
	}

	if (node.GetName().compare(L"date")==0)
	{		
		wstring sdate = node.GetText();
		wchar_t* date = (wchar_t *) sdate.c_str();
		int params;
		SYSTEMTIME stime = { 0 };
		FILETIME ftime = { 0 };

		params = swscanf_s(date, L"%04d-%02d-%02dT%02d:%02d:%02d",
			&stime.wYear, &stime.wMonth,  &stime.wDay,
			&stime.wHour, &stime.wMinute, &stime.wSecond);

		if (params == NUMBER_OF_PARMS)
		{
			_LARGE_INTEGER ulong;

			SystemTimeToFileTime(&stime, &ftime);		

			ulong.LowPart = ftime.dwLowDateTime;
			ulong.HighPart = ftime.dwHighDateTime;
			m_configuration.SetDateTime(ulong);
		}
	}
}