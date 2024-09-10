// Create a char* from a unicode CString
//
char* CConnexionSocket::GetAsciiString( CString Str )
{
	char* NewStr = (char*) malloc(Str.GetLength()+1);

	for( int i=0; i<Str.GetLength(); i++ )
	{
		unsigned short us = _mbbtombc( Str.GetAt(i) );
		if( us<256 )
			NewStr[i] = (char) us;
		else
			NewStr[i] = ' ';
	}
	NewStr[Str.GetLength()] = 0;

	return NewStr;
}