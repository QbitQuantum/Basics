void task_user_cli( ) {
	char c;
	char cbuff_storage[CONFIG_CLI_MAX_CHARACTERS];
	struct char_buffer cbuff;
	cbuffer_init( &cbuff, cbuff_storage, CONFIG_CLI_MAX_CHARACTERS );

	//used for parsing out the first token
	char first_token[CONFIG_CLI_MAX_CHARACTERS];

	//keep track of which track we are
	int track = TRACK_UNINITIALIZED;

	//Copy of track data
	struct track_node track_data[TRACK_MAX];

	//for complex prints
	struct print_buffer pbuff;
	ap_init_buff( &pbuff );

	//go to the CLI location, and save it
	Printf( COM2, "\x1B[24;20f\x1B[s" );

	while( 1 ) {
		ap_init_buff( &pbuff );
		c = Getc( COM2 );

		//catch special characters
		switch( c ) {
			case CHAR_GRAVE_ACCENT:
				CommandOutput( "[CLI] ABORT!" );
				Abort( );
				break;
			case CHAR_BACKSPACE:
				if( cbuff.state == CBUFF_EMPTY ) {
					break;
				} //do nothing if empty

				//remove the last character
				cbuffer_pop_last( &cbuff );

				//move the cursor back one space and delete the character
				Printf( COM2, "\x1B[u\x1B[D\x1B[K\x1B[s" );

				break;
			case CHAR_PERIOD:
				TabRight( );
				break;
			case CHAR_COMMA:
				TabLeft( );
				break;
			case CHAR_NEWLINE:
			case CHAR_ENTER:
				if( cbuff.state == CBUFF_EMPTY ) {
					break;
				} //do nothing if empty

				//we need to parse, get the first token
				if( next_token( &cbuff, first_token ) == 0 ) {
					break;
				} //we were just spaces

				//now check which command the first token matches
				if( strcmp( first_token, "tr" ) == 0 ) {
					command_tr( &cbuff );
				} else if( strcmp( first_token, "q" ) == 0 ) {
					command_q( &cbuff );
				} else if( strcmp( first_token, "game" ) == 0 ) {
					command_game( &cbuff );
				} else if( strcmp( first_token, "wh" ) == 0 ) {
					command_wh( &cbuff );
				} else if( strcmp( first_token, "st" ) == 0 ) {
					command_st( &cbuff );
				} else if( strcmp( first_token, "sw" ) == 0 ) {
					command_sw( &cbuff );
				} else if( strcmp( first_token, "swa" ) == 0 ) {
					command_swa( &cbuff );
				} else if( strcmp( first_token, "rv" ) == 0 ) {
					command_rv( &cbuff );
				} else if( strcmp( first_token, "add" ) == 0 ) {
					command_add( &cbuff, track );
				} else if( strcmp( first_token, "echo" ) == 0 ) {
					command_echo( &cbuff );
				} else if( strcmp( first_token, "delay" ) == 0 ) {
					command_delay( &cbuff );
				} else if( strcmp( first_token, "beep" ) == 0 ) {
					command_beep( &cbuff );
				} else if( strcmp( first_token, "looptest" ) == 0 ) {
					command_looptest( &cbuff );
				} else if( strcmp( first_token, "zombtest" ) == 0 ) {
					command_zombtest( &cbuff );
				} else if( strcmp( first_token, "track" ) == 0 ) {
					command_track( &cbuff, &track, track_data );
				} else if( strcmp( first_token, "sos" ) == 0 ) {
					command_sos( &cbuff );
				} else if( strcmp( first_token, "calibrationout" ) == 0 ) {
					command_calibrationout( &cbuff );
				} else if( strcmp( first_token, "route" ) == 0 ) {
					command_route( &cbuff, track_data );
				} else if( strcmp( first_token, "tdir" ) == 0 ) {
					command_tdir( &cbuff );
				} else if( strcmp( first_token, "resv" ) == 0 ) {
					command_resv( &cbuff, track_data );
				} else if( strcmp( first_token, "free" ) == 0 ) {
					command_free( &cbuff, track_data );
				} else {
					CommandOutput( "Invalid Command" );
				}


				//empty the command buffer
				cbuffer_empty( &cbuff );
				//clear the command line
				Printf( COM2, "\x1B[24;20f\x1B[K\x1B[s" );

				break;
			default:
				//if it is not a valid character ignore it
				if( !validate_char( &c ) ) {
					break;
				}
				//if we are full, ignore the character
				if( cbuff.state == CBUFF_FULL ) {
					break;
				}

				//we have a valid character buffer and print it
				cbuffer_push_char( &cbuff, c );
				Printf( COM2, "\x1B[u%c\x1B[s", c );
				break;
		}

		//re-initialize the parse
		first_token[0] = '\0';
	}
}