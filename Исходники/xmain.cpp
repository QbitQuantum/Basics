int PASCAL WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	strcpy ( szMap, lpCmdLine );
	//strcpy ( szMap, "csg1.x" );

		char szFinal  [ 256 ];
	
	memset ( szFinal, 0, sizeof ( szFinal ) );

	for ( int iTemp = strlen ( szMap ); iTemp > 0; iTemp-- )
	{
		if ( szMap [ iTemp ] == '/' || szMap [ iTemp ] == '\\' )
		{
			memcpy ( szFinal, &szMap [ iTemp + 1 ], sizeof ( char ) * iTemp );

			break;
		}
	}

	strcpy ( szMap, szFinal );

//MessageBox ( NULL, szFinal, "info", MB_OK );

	//MessageBox ( NULL, szMap, "info", MB_OK );
	//MessageBox ( NULL, lpCmdLine, "lpCmdLine", MB_OK );

	hInst		  = hInstance;
    hPrevInstance = hPrevInstance;

	MSG			msg;

	BOOL		perf_flag	= FALSE;
	LONGLONG	last_time	= 0;
	LONGLONG	cur_time;
	LONGLONG	perf_cnt;
	float		time_scale;
	
	if ( !doInit ( hInst, nCmdShow ) ) 
		return FALSE;
	
	if ( QueryPerformanceFrequency ( ( LARGE_INTEGER* ) &perf_cnt ) )
	{ 
		QueryPerformanceCounter ( ( LARGE_INTEGER* ) &last_time );
		time_scale	= 1.0f / perf_cnt;
		perf_flag	= TRUE;
	}
	else
	{
		last_time	= timeGetTime ( );
		time_scale	= 0.001f;
	} 	

	// SetCursorPos ( 320,200 );
    // ShowCursor ( FALSE );

    BOOL bGotMsg;

	while ( quit != 1 )
	{
		while ( bGotMsg = PeekMessage ( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage ( &msg );
            DispatchMessage  ( &msg );
        }

		if ( rendering == 1 )
		{
			if ( perf_flag ) 
				QueryPerformanceCounter ( ( LARGE_INTEGER* ) &cur_time );
			else 
				cur_time = timeGetTime ( ); 

			time_elapsed = ( cur_time - last_time ) * time_scale;
			last_time	 = cur_time;
	
			// CheckInput  ( );
			// renderframe ( );
		}
    }

	ShowCursor ( TRUE );

	return msg.wParam;
}