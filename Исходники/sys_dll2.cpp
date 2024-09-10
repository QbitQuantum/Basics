void EatTextModeKeyPresses()
{
	if ( !g_bTextMode )
		return;
	
	static bool bFirstRun = true;
	if ( bFirstRun )
	{
		bFirstRun = false;
		MoveConsoleWindowToFront();
	}

	char ch;
	while ( (ch = NextGetch()) != -1 )
	{
		if ( ch == 8 )
		{
			// Backspace..
			if ( g_TextModeLine.Count() )
			{
				g_TextModeLine.Remove( g_TextModeLine.Count() - 1 );
			}
		}
		else if ( ch == '\r' )
		{
			// Finish the line.
			if ( g_TextModeLine.Count() )
			{
				g_TextModeLine.AddMultipleToTail( 2, "\n" );
				Cbuf_AddText( g_TextModeLine.Base() );
				g_TextModeLine.Purge();
			}
			printf( "\n" );
		}
		else
		{
			g_TextModeLine.AddToTail( ch );
		}

		printf( "%c", ch );
	}	
}