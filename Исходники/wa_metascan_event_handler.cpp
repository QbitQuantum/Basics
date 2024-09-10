void WaMetascanEventHandler::_breakRestIP( std::wstring& rest_ip, std::wstring& url, std::wstring& other )
{
	wchar_t p_directory[_MAX_DIR];
	wchar_t p_filename[_MAX_FNAME];

	_wsplitpath( rest_ip.c_str(), NULL, p_directory, p_filename, NULL );
	std::wstring s_temp = p_directory;
	other = p_filename;

	size_t i = s_temp.length() - 1;
	for ( ; i > 0 ; i-- )
	{
		if ( s_temp[i] == L':')
			break;
	}

	if ( i == 0 )
		url = s_temp.substr( 0, s_temp.length() - 1 );
	else
		url = s_temp.substr( 0, i );
}