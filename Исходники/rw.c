/** Main function. */
int main( ) {
	char ch;
	int run = 1;

	clrscr( );

	dispmenu( );

	/* Loop for keyboard input. */
	do {
		/* Get keyboard input character. */
		ch = getch( );

		gotoxy( 24, 17 );

		switch ( ch ) {
		case '1':
			if ( spawnlp( P_WAIT, "RWMAIN.COM", "RWMAIN.COM", NULL ) == -1 ) {
				puts( "Cannot find file : RWMAIN.COM" );
				getch( );
			}
			clrscr( );
			dispmenu( );
			break;
		case '2':
			if ( spawnlp( P_WAIT, "NLQ.EXE", "NLQ.EXE", NULL ) == -1 ) {
				puts( "  Cannot find file : NLQ.EXE " );
				getch( );
			}
			clrscr( );
			dispmenu( );
			break;
		case '3':
			puts( "        Not implemented.     " );
			getch( );
			clrscr( );
			dispmenu( );
			break;
		case '4':
		case 27:								/* escape key */
			run = 0;
			break;
		default:
			puts( "  Please select number 1-4   " );
		}

		gotoxy( 20, 19 );

	} while ( run );

	exit( 0 );
}