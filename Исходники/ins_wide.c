static void
test_inserts(int level)
{
    static bool first = TRUE;

    int ch;
    int limit;
    int row = 1;
    int col;
    int row2, col2;
    int length;
    wchar_t buffer[BUFSIZ];
    WINDOW *look = 0;
    WINDOW *work = 0;
    WINDOW *show = 0;
    int margin = (2 * MY_TABSIZE) - 1;
    Options option = ((m_opt ? oMove : oDefault)
		      | ((w_opt || (level > 0)) ? oWindow : oDefault));

    if (first) {
	static char cmd[80];
	setlocale(LC_ALL, "");

	putenv(strcpy(cmd, "TABSIZE=8"));

	initscr();
	(void) cbreak();	/* take input chars one at a time, no wait for \n */
	(void) noecho();	/* don't echo input */
	keypad(stdscr, TRUE);
    }

    limit = LINES - 5;
    if (level > 0) {
	look = newwin(limit, COLS - (2 * (level - 1)), 0, level - 1);
	work = newwin(limit - 2, COLS - (2 * level), 1, level);
	show = newwin(4, COLS, limit + 1, 0);
	box(look, 0, 0);
	wnoutrefresh(look);
	limit -= 2;
    } else {
	work = stdscr;
	show = derwin(stdscr, 4, COLS, limit + 1, 0);
    }
    keypad(work, TRUE);

    for (col = margin + 1; col < COLS; col += MY_TABSIZE)
	MvWVLine(work, row, col, '.', limit - 2);

    MvWVLine(work, row, margin, ACS_VLINE, limit - 2);
    MvWVLine(work, row, margin + 1, ACS_VLINE, limit - 2);
    limit /= 2;

    MvWAddStr(work, 1, 2, "String");
    MvWAddStr(work, limit + 1, 2, "Chars");
    wnoutrefresh(work);

    buffer[length = 0] = '\0';
    legend(show, level, option, buffer, length);
    wnoutrefresh(show);

    doupdate();

    /*
     * Show the characters inserted in color, to distinguish from those that
     * are shifted.
     */
    if (has_colors()) {
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	wbkgdset(work, COLOR_PAIR(1) | ' ');
    }

    while ((ch = read_linedata(work)) != ERR && !isQUIT(ch)) {
	wmove(work, row, margin + 1);
	switch (ch) {
	case key_RECUR:
	    test_inserts(level + 1);

	    touchwin(look);
	    touchwin(work);
	    touchwin(show);

	    wnoutrefresh(look);
	    wnoutrefresh(work);
	    wnoutrefresh(show);

	    doupdate();
	    break;
	case key_NEWLINE:
	    if (row < limit) {
		++row;
		/* put the whole string in, all at once */
		col2 = margin + 1;
		switch (option) {
		case oDefault:
		    if (n_opt > 1) {
			for (col = 0; col < length; col += n_opt) {
			    col2 = ColOf(buffer, col, margin);
			    if (move(row, col2) != ERR) {
				InsNStr(buffer + col, LEN(col));
			    }
			}
		    } else {
			if (move(row, col2) != ERR) {
			    InsStr(buffer);
			}
		    }
		    break;
		case oMove:
		    if (n_opt > 1) {
			for (col = 0; col < length; col += n_opt) {
			    col2 = ColOf(buffer, col, margin);
			    MvInsNStr(row, col2, buffer + col, LEN(col));
			}
		    } else {
			MvInsStr(row, col2, buffer);
		    }
		    break;
		case oWindow:
		    if (n_opt > 1) {
			for (col = 0; col < length; col += n_opt) {
			    col2 = ColOf(buffer, col, margin);
			    if (wmove(work, row, col2) != ERR) {
				WInsNStr(work, buffer + col, LEN(col));
			    }
			}
		    } else {
			if (wmove(work, row, col2) != ERR) {
			    WInsStr(work, buffer);
			}
		    }
		    break;
		case oMoveWindow:
		    if (n_opt > 1) {
			for (col = 0; col < length; col += n_opt) {
			    col2 = ColOf(buffer, col, margin);
			    MvWInsNStr(work, row, col2, buffer + col, LEN(col));
			}
		    } else {
			MvWInsStr(work, row, col2, buffer);
		    }
		    break;
		}

		/* do the corresponding single-character insertion */
		row2 = limit + row;
		for (col = 0; col < length; ++col) {
		    col2 = ColOf(buffer, col, margin);
		    switch (option) {
		    case oDefault:
			if (move(row2, col2) != ERR) {
			    InsCh((chtype) buffer[col]);
			}
			break;
		    case oMove:
			MvInsCh(row2, col2, (chtype) buffer[col]);
			break;
		    case oWindow:
			if (wmove(work, row2, col2) != ERR) {
			    WInsCh(work, (chtype) buffer[col]);
			}
			break;
		    case oMoveWindow:
			MvWInsCh(work, row2, col2, (chtype) buffer[col]);
			break;
		    }
		}
	    } else {
		beep();
	    }
	    break;
	default:
	    buffer[length++] = ch;
	    buffer[length] = '\0';

	    /* put the string in, one character at a time */
	    col = ColOf(buffer, length - 1, margin);
	    switch (option) {
	    case oDefault:
		if (move(row, col) != ERR) {
		    InsStr(buffer + length - 1);
		}
		break;
	    case oMove:
		MvInsStr(row, col, buffer + length - 1);
		break;
	    case oWindow:
		if (wmove(work, row, col) != ERR) {
		    WInsStr(work, buffer + length - 1);
		}
		break;
	    case oMoveWindow:
		MvWInsStr(work, row, col, buffer + length - 1);
		break;
	    }

	    /* do the corresponding single-character insertion */
	    switch (option) {
	    case oDefault:
		if (move(limit + row, col) != ERR) {
		    InsCh((chtype) ch);
		}
		break;
	    case oMove:
		MvInsCh(limit + row, col, (chtype) ch);
		break;
	    case oWindow:
		if (wmove(work, limit + row, col) != ERR) {
		    WInsCh(work, (chtype) ch);
		}
		break;
	    case oMoveWindow:
		MvWInsCh(work, limit + row, col, (chtype) ch);
		break;
	    }

	    wnoutrefresh(work);

	    legend(show, level, option, buffer, length);
	    wnoutrefresh(show);

	    doupdate();
	    break;
	}
    }
    if (level > 0) {
	delwin(show);
	delwin(work);
	delwin(look);
    }
}