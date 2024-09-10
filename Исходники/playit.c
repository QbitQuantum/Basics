/*
 * playit:
 *	Play a given game, handling all the curses commands from
 *	the driver.
 */
void
playit(void)
{
	int ch;
	int y, x;
	uint32_t version;
	ssize_t result;

	result = read(huntsocket, &version, sizeof(version));
	if (result != (ssize_t)sizeof(version)) {
		bad_con();
		/* NOTREACHED */
	}
	if (ntohl(version) != (uint32_t)HUNT_VERSION) {
		bad_ver();
		/* NOTREACHED */
	}
	errno = 0;
#ifdef OTTO
	Otto_count = 0;
#endif
	nchar_send = MAX_SEND;
	while ((ch = GETCHR()) != EOF) {
#ifdef DEBUG
		fputc(ch, stderr);
#endif
		switch (ch & 0377) {
		  case MOVE:
			y = GETCHR();
			x = GETCHR();
			move(y, x);
			break;
		  case ADDCH:
			ch = GETCHR();
#ifdef OTTO
			switch (ch) {

			case '<':
			case '>':
			case '^':
			case 'v':
				otto_face = ch;
				getyx(stdscr, otto_y, otto_x);
				break;
			}
#endif
			addch(ch);
			break;
		  case CLRTOEOL:
			clrtoeol();
			break;
		  case CLEAR:
			clear_the_screen();
			break;
		  case REFRESH:
			refresh();
			break;
		  case REDRAW:
			redraw_screen();
			refresh();
			break;
		  case ENDWIN:
			refresh();
			if ((ch = GETCHR()) == LAST_PLAYER)
				Last_player = true;
			ch = EOF;
			goto out;
		  case BELL:
			beep();
			break;
		  case READY:
			refresh();
			if (nchar_send < 0)
				tcflush(STDIN_FILENO, TCIFLUSH);
			nchar_send = MAX_SEND;
#ifndef OTTO
			(void) GETCHR();
#else
			Otto_count -= (GETCHR() & 0xff);
			if (!Am_monitor) {
#ifdef DEBUG
				fputc('0' + Otto_count, stderr);
#endif
				if (Otto_count == 0 && Otto_mode)
					otto(otto_y, otto_x, otto_face);
			}
#endif
			break;
		  default:
#ifdef OTTO
			switch (ch) {

			case '<':
			case '>':
			case '^':
			case 'v':
				otto_face = ch;
				getyx(stdscr, otto_y, otto_x);
				break;
			}
#endif
			addch(ch);
			break;
		}
	}
out:
	(void) close(huntsocket);
}