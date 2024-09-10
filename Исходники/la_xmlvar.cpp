long LXMLVar::What( const QChar S )
//            ~~~~
{
	for(;;)
	{
		if( S.isLetter() || (S == _T('_')) )
			return 1;
		if( S.isDigit() || ( S == _T('-') ) || ( S == _T('.') ) )
			return 2;
		if( S == _T(':') )
			return 3;
		return 0;
	}
}