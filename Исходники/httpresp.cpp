void CServerHttpResp::RemoveHeader( const char* header )
{
	CQString temp;
	temp = header ;
	temp.ToLower() ;

	CHeaderMap::iterator iter ;
	iter = _HeaderMap.find( temp ) ;
	if ( iter != _HeaderMap.end() )
		_HeaderMap.erase( iter ) ;
}