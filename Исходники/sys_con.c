/*
================
Con_SetFocus

change focus to console hwnd 
================
*/
void Con_RegisterHotkeys( void )
{
	SetFocus( s_wcd.hWnd );

	// user can hit escape for quit
	RegisterHotKey( s_wcd.hWnd, QUIT_ON_ESCAPE_ID, 0, VK_ESCAPE );
}