BOOL Script( LPCSTR lpszFileName )
{
	CScanner s;

	if( s.Load( lpszFileName ) )
	{
		s.GetToken();
		while( s.tok != FINISHED )
		{
			if( s.Token == "Core" )
			{
				s.GetToken();
				strcpy( g_szCoreAddr, s.Token );
			}
			else if( s.Token == "Port" )
			{
				g_uPort = s.GetNumber();		
			}
			s.GetToken();
		}
		return TRUE;
	}
	Error( "Can't open file, %s.\n", lpszFileName );
	return FALSE;
};