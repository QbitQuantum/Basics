static int
test_inchs(int level, char **argv, WINDOW *chrwin, WINDOW *strwin)
{
    WINDOW *txtbox = 0;
    WINDOW *txtwin = 0;
    FILE *fp;
    int j;
    int txt_x = 0, txt_y = 0;
    int base_y;
    int limit;
    cchar_t ch;
    cchar_t text[MAX_COLS];

    if (argv[level] == 0) {
	beep();
	return FALSE;
    }

    if (level > 1) {
	txtbox = newwin(LINES - BASE_Y, COLS - level, BASE_Y, level);
	box(txtbox, 0, 0);
	wnoutrefresh(txtbox);

	txtwin = derwin(txtbox,
			getmaxy(txtbox) - 2,
			getmaxx(txtbox) - 2,
			1, 1);
	base_y = 0;
    } else {
	txtwin = stdscr;
	base_y = BASE_Y;
    }

    keypad(txtwin, TRUE);	/* enable keyboard mapping */
    (void) cbreak();		/* take input chars one at a time, no wait for \n */
    (void) noecho();		/* don't echo input */

    txt_y = base_y;
    txt_x = 0;
    wmove(txtwin, txt_y, txt_x);

    if ((fp = fopen(argv[level], "r")) != 0) {
	while ((j = fgetc(fp)) != EOF) {
	    if (waddch(txtwin, UChar(j)) != OK) {
		break;
	    }
	}
	fclose(fp);
    } else {
	wprintw(txtwin, "Cannot open:\n%s", argv[1]);
    }

    while (!Quit(j = mvwgetch(txtwin, txt_y, txt_x))) {
	switch (j) {
	case KEY_DOWN:
	case 'j':
	    if (txt_y < getmaxy(txtwin) - 1)
		txt_y++;
	    else
		beep();
	    break;
	case KEY_UP:
	case 'k':
	    if (txt_y > base_y)
		txt_y--;
	    else
		beep();
	    break;
	case KEY_LEFT:
	case 'h':
	    if (txt_x > 0)
		txt_x--;
	    else
		beep();
	    break;
	case KEY_RIGHT:
	case 'l':
	    if (txt_x < getmaxx(txtwin) - 1)
		txt_x++;
	    else
		beep();
	    break;
	case 'w':
	    test_inchs(level + 1, argv, chrwin, strwin);
	    if (txtbox != 0) {
		touchwin(txtbox);
		wnoutrefresh(txtbox);
	    } else {
		touchwin(txtwin);
		wnoutrefresh(txtwin);
	    }
	    break;
	default:
	    beep();
	    break;
	}

	MvWPrintw(chrwin, 0, 0, "char:");
	wclrtoeol(chrwin);

	if (txtwin != stdscr) {
	    wmove(txtwin, txt_y, txt_x);
	    if (win_wch(txtwin, &ch) != ERR) {
		if (wadd_wch(chrwin, &ch) != ERR) {
		    for (j = txt_x + 1; j < getmaxx(txtwin); ++j) {
			if (mvwin_wch(txtwin, txt_y, j, &ch) != ERR) {
			    if (wadd_wch(chrwin, &ch) == ERR) {
				break;
			    }
			} else {
			    break;
			}
		    }
		}
	    }
	} else {
	    move(txt_y, txt_x);
	    if (in_wch(&ch) != ERR) {
		if (wadd_wch(chrwin, &ch) != ERR) {
		    for (j = txt_x + 1; j < getmaxx(txtwin); ++j) {
			if (mvin_wch(txt_y, j, &ch) != ERR) {
			    if (wadd_wch(chrwin, &ch) == ERR) {
				break;
			    }
			} else {
			    break;
			}
		    }
		}
	    }
	}
	wnoutrefresh(chrwin);

	MvWPrintw(strwin, 0, 0, "text:");
	wclrtobot(strwin);

	limit = getmaxx(strwin) - 5;

	if (txtwin != stdscr) {
	    wmove(txtwin, txt_y, txt_x);
	    if (win_wchstr(txtwin, text) != ERR) {
		(void) mvwadd_wchstr(strwin, 0, 5, text);
	    }

	    wmove(txtwin, txt_y, txt_x);
	    if (win_wchnstr(txtwin, text, limit) != ERR) {
		(void) mvwadd_wchstr(strwin, 1, 5, text);
	    }

	    if (mvwin_wchstr(txtwin, txt_y, txt_x, text) != ERR) {
		(void) mvwadd_wchstr(strwin, 2, 5, text);
	    }

	    if (mvwin_wchnstr(txtwin, txt_y, txt_x, text, limit) != ERR) {
		(void) mvwadd_wchstr(strwin, 3, 5, text);
	    }
	} else {
	    move(txt_y, txt_x);
	    if (in_wchstr(text) != ERR) {
		(void) mvwadd_wchstr(strwin, 0, 5, text);
	    }

	    move(txt_y, txt_x);
	    if (in_wchnstr(text, limit) != ERR) {
		(void) mvwadd_wchstr(strwin, 1, 5, text);
	    }

	    if (mvin_wchstr(txt_y, txt_x, text) != ERR) {
		(void) mvwadd_wchstr(strwin, 2, 5, text);
	    }

	    if (mvin_wchnstr(txt_y, txt_x, text, limit) != ERR) {
		(void) mvwadd_wchstr(strwin, 3, 5, text);
	    }
	}

	wnoutrefresh(strwin);
    }
    if (level > 1) {
	delwin(txtwin);
	delwin(txtbox);
    }
    return TRUE;
}