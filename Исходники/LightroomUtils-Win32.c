static int _selectNextPhoto( lua_State *L )
{
	int retVal = 0;
	if( lua_gettop( L ) == 0 )
	{
/*		INPUT input[ 2 ] = {0};
		input[ 0 ].type = INPUT_KEYBOARD;
		input[ 0 ].ki.wVk = VK_RIGHT;
		input[ 0 ].ki.dwFlags = 0;

		input[ 1 ].type = INPUT_KEYBOARD;
		input[ 1 ].ki.wVk = VK_RIGHT;
		input[ 1 ].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput( sizeof( input ) / sizeof( input[ 0 ] ), 
				   input,
				   sizeof( INPUT ) );
*/
		keybd_event( VK_RIGHT, MapVirtualKey( LOBYTE( VkKeyScan( VK_RIGHT ) ), 0 ), 0, 0 );
		Sleep( 50 );
		keybd_event( VK_RIGHT, MapVirtualKey( LOBYTE( VkKeyScan( VK_RIGHT ) ), 0 ), 0, KEYEVENTF_KEYUP );

	} // if
	return( 0 );

} // _selectNextPhoto