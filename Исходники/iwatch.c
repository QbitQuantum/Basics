int
display(BUFFER * cur, BUFFER * prev, reverse_mode_t reverse)
{
	int	 i, val, screen_x, screen_y, cw, line, rl;
	char	*ct;

	erase();

	move(0, 0);
	if ((int)strlen(cmdstr) > COLS - 47)
		printw("\"%-.*s..\" ", COLS - 49, cmdstr);
	else
		printw("\"%s\" ", cmdstr);
	if (pause_status)
		printw("--PAUSE--");
	else if (opt_interval.tv_sec == 1 && opt_interval.tv_usec == 0)
		printw("on every second");
	else if (opt_interval.tv_usec == 0)
		printw("on every %d seconds", (int)opt_interval.tv_sec);
	else {
		for (i = NUM_FRAQ_DIGITS_USEC, val = opt_interval.tv_usec;
		    val % 10 == 0; val /= 10)
			i--;
		printw("on every %d.%0*d seconds",
		    (int)opt_interval.tv_sec, i, val);
	}

	ct = ctime(&lastupdate);
	ct[24] = '\0';
	move(0, COLS - strlen(ct));
	addstr(ct);

#define MODELINE(HOTKEY,SWITCH,MODE)				\
	do {							\
		printw(HOTKEY);					\
		if (reverse == SWITCH) attron(style);		\
		printw(MODE);					\
		if (reverse == SWITCH) attrset(A_NORMAL);	\
	} while (0/* CONSTCOND */)

	move(1, COLS - 47);
	printw("Reverse mode:");
	MODELINE(" [w]", REVERSE_WORD, "word");
	MODELINE(" [e]", REVERSE_LINE, "line");
	MODELINE(" [r]", REVERSE_CHAR, "char");
	printw(" [t]toggle");

	move(1, 1);
	if (prefix >= 0) {
		if (decimal_point > 0) {
			int power10;

			for (i = 0, power10 = 1; i < decimal_point; i++)
				power10 *= 10;

			printw("%d.%0*d", prefix / power10, decimal_point,
			    prefix % power10);
		} else if (decimal_point == 0)
			printw("%d. ", prefix);
		else
			printw("%d ", prefix);
	}

	if (start_line != 0 || start_column != 0)
		printw("(%d, %d)", start_line, start_column);

	if (!prev || (cur == prev))
		reverse = REVERSE_NONE;

	for (line = start_line, screen_y = 2;
	    screen_y < LINES && line < MAXLINE && (*cur)[line][0];
	    line++, screen_y++) {
		wchar_t	*cur_line, *prev_line, *p, *pp;

		rl = 0;	/* reversing line */
		cur_line = (*cur)[line];
		prev_line = (*prev)[line];

		for (p = cur_line, cw = 0; cw < start_column; p++)
			cw += WCWIDTH(*p);
		screen_x = cw - start_column;
		for (pp = prev_line, cw = 0; cw < start_column; pp++)
			cw += WCWIDTH(*pp);

		switch (reverse) {
		case REVERSE_LINE:
			if (wcscmp(cur_line, prev_line)) {
				attron(style);
				rl = 1;
				for (i = 0; i < screen_x; i++) {
					move(screen_y, i);
					addch(' ');
				}
			}
			/* FALLTHROUGH */

		case REVERSE_NONE:
			move(screen_y, screen_x);
			while (screen_x < COLS) {
				if (*p && *p != L'\n') {
					cw = wcwidth(*p);
					if (screen_x + cw >= COLS)
						break;
					addwch(*p++);
					pp++;
					screen_x += cw;
				} else if (rl) {
					addch(' ');
					screen_x++;
				} else
					break;
			}
			attrset(A_NORMAL);
			break;

		case REVERSE_WORD:
		case REVERSE_CHAR:
			move(screen_y, screen_x);
			while (*p && screen_x < COLS) {
				cw = wcwidth(*p);
				if (screen_x + cw >= COLS)
					break;
				if (*p == *pp) {
					addwch(*p++);
					pp++;
					screen_x += cw;
					continue;
				}
				/*
				 * This method to reverse by word unit is not
				 * very fancy but it was easy to implement.  If
				 * you are urged to rewrite this algorithm, it
				 * is right thing and don't hesitate to do so!
				 */
				/*
				 * If the word reverse option is specified and
				 * the current character is not a space, track
				 * back to the beginning of the word.
				 */
				if (reverse == REVERSE_WORD && !iswspace(*p)) {
					while (cur_line + start_column < p &&
					    !iswspace(*(p - 1))) {
						p--;
						pp--;
						screen_x -= wcwidth(*p);
					}
					move(screen_y, screen_x);
				}
				attron(style);

				/* Print character itself.  */
				cw = wcwidth(*p);
				addwch(*p++);
				pp++;
				screen_x += cw;

				/*
				 * If the word reverse option is specified, and
				 * the current character is not a space, print
				 * the whole word which includes current
				 * character.
				 */
				if (reverse == REVERSE_WORD) {
					while (*p && !iswspace(*p) &&
					    screen_x < COLS) {
						cw = wcwidth(*p);
						addwch(*p++);
						pp++;
						screen_x += cw;
					}
				}
				attrset(A_NORMAL);
			}
			break;
		}
	}
	move(1, 0);
	refresh();
	return (1);
}