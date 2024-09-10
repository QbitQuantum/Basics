/*
=====================
	ParseCmd
=====================
*/
static int ParseCmd( TCHAR *szIn, TCHAR *szOut ) {
	conCmd_t command;
	TCHAR szBuff[CON_STRING_SIZE];
	int i;

	if( (szIn == NULL) || (szOut == NULL) ) {
		return 0;
	}
	
	//init "return string"
	N_Strcpy( szOut, TEXT( "invalid command" ) );
	
	if( szIn[0] == '/' ) {
		szIn++;

		//extract useful information from command buffer
		//
		while( *szIn ) {
			N_Memset( szBuff, 0, sizeof(TCHAR)*CON_STRING_SIZE );
			i = 0;
			while( *szIn && (i < CON_STRING_SIZE) ) {
				szBuff[i++] = *(szIn++);
				if( (command = SeeCmd( szBuff )) != CON_INVALID ) {
					break;
				}
			}
			
			switch( command ) {
				case CMD_SET:
					//hacky...
					szIn -= 3;
					if( cfExecute( szIn, N_Strlen( szIn ) ) ) {
						N_Strcpy( szOut, TEXT( "success..." ) );
					}
					else {
						N_Strcpy( szOut, TEXT( "failed..." ) );
					}
					szIn[0] = 0;
					break;
				
				case CMD_SAVECONFIG:
					if( cfSaveTable() ) {
						N_Strcpy( szOut, TEXT( "config saved" ) );
					}
					else {
						N_Strcpy( szOut, TEXT( "could not save config" ) );
					}
					break;
				
				case CMD_QUIT:
					PostQuitMessage( 0 );
					N_Strcpy( szOut, TEXT( "quiting..." ) );
					break;
				
				case CMD_ABOUT:
					N_Sprintf( szOut, CON_STRING_SIZE,
						TEXT( " Netrix \xA9 2005 dimovich\r\n  current version is %s" ), NETRIX_VERSION );
					break;
				
				case CMD_LOADRES:
					reloadResources();
					N_Strcpy( szOut, TEXT( "resources reloaded" ) );
					break;
				
				case CMD_TESTBOT:
					TestBot( &szIn );
					break;

				default:
					break;
			}
		}
	}
	else {
		N_Strncpy( szOut, szIn, CON_STRING_SIZE );
		return 0;
	}
	
	return 1;
}