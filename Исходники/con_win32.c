/*
==================
CON_Shutdown
==================
*/
void CON_Shutdown( void )
{
	SetConsoleMode( qconsole_hin, qconsole_orig_mode );
	SetConsoleCursorInfo( qconsole_hout, &qconsole_orig_cursorinfo );
	CloseHandle( qconsole_hout );
	CloseHandle( qconsole_hin );
}