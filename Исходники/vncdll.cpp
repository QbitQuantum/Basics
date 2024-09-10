/*
 * Switch to the input desktop and set it as this threads desktop.
 */
HDESK vncdll_getinputdesktop( BOOL bSwitchStation )
{
	DWORD dwResult         = ERROR_ACCESS_DENIED;
	HWINSTA hWindowStation = NULL;
	HDESK hInputDesktop    = NULL;
	HWND hDesktopWnd       = NULL;	

	do
	{
		if( bSwitchStation )
		{
			// open the WinSta0 as some services are attached to a different window station.
			hWindowStation = OpenWindowStation( "WinSta0", FALSE, WINSTA_ALL_ACCESS );
			if( !hWindowStation )
			{
				if( RevertToSelf() )
					hWindowStation = OpenWindowStation( "WinSta0", FALSE, WINSTA_ALL_ACCESS );
			}
			
			// if we cant open the defaut input station we wont be able to take a screenshot
			if( !hWindowStation )
				BREAK_WITH_ERROR( "[VNCDLL] vncdll_getinputdesktop: Couldnt get the WinSta0 Window Station", ERROR_INVALID_HANDLE );
			
			// set the host process's window station to this sessions default input station we opened
			if( !SetProcessWindowStation( hWindowStation ) )
				BREAK_ON_ERROR( "[VNCDLL] vncdll_getinputdesktop: SetProcessWindowStation failed" );
		}

		// grab a handle to the default input desktop (e.g. Default or WinLogon)
		hInputDesktop = OpenInputDesktop( 0, FALSE, MAXIMUM_ALLOWED );
		if( !hInputDesktop )
			BREAK_ON_ERROR( "[VNCDLL] vncdll_getinputdesktop: OpenInputDesktop failed" );

		// set this threads desktop to that of this sessions default input desktop on WinSta0
		SetThreadDesktop( hInputDesktop );
	
	} while( 0 );

	return hInputDesktop;
}