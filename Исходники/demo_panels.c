/*
 * A command consists of one or more letter/digit pairs separated by a space.
 * Digits are limited to 1..MAX_PANELS.
 *
 * End the command with a newline.  Reject other characters.
 */
static bool
get_command(PANEL * px[MAX_PANELS + 1], char *buffer, int limit)
{
    int length = 0;
    int y0, x0;
    int c0, ch;
    WINDOW *win;

    getyx(stdscr, y0, x0);
    win = statusline();
    waddstr(win, "Command:");
    buffer[length = 0] = '\0';

    if (log_in != 0) {
	if (fgets(buffer, limit - 3, log_in) != 0) {
	    length = (int) strlen(buffer);
	    while (length > 0 && isspace(UChar(buffer[length - 1])))
		buffer[--length] = '\0';
	    waddstr(win, buffer);
	} else {
	    close_input();
	}
	(void) wgetch(win);
    } else {
	c0 = 0;
	for (;;) {
	    ch = wgetch(win);
	    if (ch == ERR || ch == QUIT || ch == ESCAPE) {
		buffer[0] = '\0';
		break;
	    } else if (ch == CTRL('L')) {
		wrefresh(curscr);
	    } else if (ch == '\n' || ch == KEY_ENTER) {
		break;
	    } else if (ch == '?') {
		show_panels(px);
	    } else if (length + 3 < limit) {
		if (ch >= KEY_MIN) {
		    beep();
		} else if (ok_letter(UChar(ch))) {
		    if (isalpha(UChar(c0))) {
			beep();
		    } else if (isdigit(UChar(c0))) {
			wprintw(win, " %c", ch);
			buffer[length++] = ' ';
			buffer[length++] = (char) (c0 = ch);
		    } else {
			wprintw(win, "%c", ch);
			buffer[length++] = (char) (c0 = ch);
		    }
		} else if (ok_digit(ch)) {
		    if (isalpha(UChar(c0))) {
			wprintw(win, "%c", ch);
			buffer[length++] = (char) (c0 = ch);
		    } else {
			beep();
		    }
		} else if (ch == ' ') {
		    if (isdigit(UChar(c0))) {
			wprintw(win, "%c", ch);
			buffer[length++] = (char) (c0 = ch);
		    } else {
			beep();
		    }
		} else {
		    beep();
		}
	    } else {
		beep();
	    }
	}
    }

    wmove(stdscr, y0, x0);

    buffer[length] = '\0';
    if (log_out && length) {
	fprintf(log_out, "%s\n", buffer);
    }
    return (length != 0);
}