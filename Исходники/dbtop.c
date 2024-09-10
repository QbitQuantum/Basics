void printHeader()
{
	int screen_height, screen_weight;
	char header_buf[ 1024 ];

	clear();
	getmaxyx( stdscr, screen_height, screen_weight );
	printString( "h,? - help; z - toggle color-mode; q,F10,Ctrl-c - quit",
			     A_NORMAL, getW (), NEWLINE );
	if( is_colorize )
      attron( COLOR_PAIR( 1 ) );

	sprintf(
			  header_buf,
			  " +User%c          .+cpu(%)  %c         . +read(B/s)%c        . +write(B/s)   %c . CAUSE    ",
			  sort_type == 3 ? '*' : ' ', !sort_type ? '*' : ' ', sort_type
				  	    == 1 ? '*' : ' ', sort_type == 2 ? '*' : ' ' );
	printString( header_buf, (is_colorize) ? A_NORMAL : A_REVERSE, getW(),
			     NEWLINE );
    if( is_colorize ) attroff( COLOR_PAIR( 1 ) );
}