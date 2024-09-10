int
main(int argc, char **argv)
{
int NTiles, FromCol, ToCol;
unsigned char AutoFlag = 0;

	switch(argc) {
	case 1:
		NTiles = DEFAULTTILES;
		break;
	case 2:
		NTiles = atoi(argv[1]);
		if (NTiles > MAXTILES || NTiles < MINTILES) {
			fprintf(stderr, "Range %d to %d\n", MINTILES, MAXTILES);
			return EXIT_FAILURE;
		}
		break;
	case 3:
		if (strcmp(argv[2], "a")) {
			Usage();
			return EXIT_FAILURE;
		}
		NTiles = atoi(argv[1]);
		if (NTiles > MAXTILES || NTiles < MINTILES) {
			fprintf(stderr, "Range %d to %d\n", MINTILES, MAXTILES);
			return EXIT_FAILURE;
		}
		AutoFlag = TRUE;
		break;
	default:
		Usage();
		return EXIT_FAILURE;
	}
#ifdef NCURSES_VERSION
	trace(TRACE_MAXIMUM);
#endif
	initscr();
	if (has_colors()) {
		int i;
		int bg = COLOR_BLACK;
		start_color();
#ifdef NCURSES_VERSION
		if (use_default_colors() == OK)
			bg = -1;
#endif
		for (i = 0; i < 9; i++)
			init_pair(i+1, bg, TileColour[i]);
	}
	cbreak();
	if (LINES < 24) {
		endwin();
		fprintf(stderr, "Min screen length 24 lines\n");
		return EXIT_FAILURE;
	}
	if(AutoFlag)
		leaveok(stdscr, TRUE);	/* Attempt to remove cursor */
	InitTiles(NTiles);
	DisplayTiles();
	if(AutoFlag) {
		do {
			noecho();
			AutoMove(0, 2, NTiles);
		} while(!Solved(NTiles));
		sleep(2);
	} else {
		echo();
		for(;;) {
			if(GetMove(&FromCol, &ToCol))
				break;
			if(InvalidMove(FromCol, ToCol)) {
				mvaddstr(STATUSLINE, 0, "Invalid Move !!");
				refresh();
				beep();
				continue;
			}
			MakeMove(FromCol, ToCol);
			if(Solved(NTiles)) {
				mvprintw(STATUSLINE, 0, "Well Done !! You did it in %d moves", NMoves);
				refresh();
				sleep(5);
				break;
			}
		}
	}
	curs_set(1);
	endwin();
	return EXIT_SUCCESS;
}