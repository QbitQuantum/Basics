static void ForcePathQuoteSpaces( WCHAR * _quotePath, const std::wstring & _path )
{
	if( _path.empty() == true )
	{
		wcscpy_s( _quotePath, 2, L"" );

		return;
	}

	std::wstring true_path = _path;

	if( _path[0] == L'/' )
	{
		true_path[0] = true_path[1];
		true_path[1] = L':';
	}

	const WCHAR * pathBuffer = true_path.c_str();
	size_t pathSize = true_path.size();

	PathCanonicalize( _quotePath, pathBuffer );
	if( PathQuoteSpaces( _quotePath ) == FALSE )
	{
		wmemmove( _quotePath + 1, _quotePath, pathSize );
		_quotePath[0] = '\"';
		_quotePath[pathSize + 1] = '\"';
		_quotePath[pathSize + 2] = 0;
	}
};