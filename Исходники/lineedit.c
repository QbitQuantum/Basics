/* Returns:
 * -1 on read errors or EOF, or on bare Ctrl-D.
 * 0  on ctrl-C,
 * >0 length of input string, including terminating '\n'
 */
int read_line_input(const char* prompt, char* command, int maxsize, line_input_t *st)
{
	int lastWasTab = FALSE;
	unsigned int ic;
	unsigned char c;
	smallint break_out = 0;
#if ENABLE_FEATURE_EDITING_VI
	smallint vi_cmdmode = 0;
	smalluint prevc;
#endif

	if (maxsize > MAX_LINELEN)
		maxsize = MAX_LINELEN;

	/* With null flags, no other fields are ever used */
	state = st ? st : (line_input_t*) &const_int_0;
#if ENABLE_FEATURE_EDITING_SAVEHISTORY
	if ((state->flags & SAVE_HISTORY) && state->hist_file)
		load_history(state->hist_file);
#endif

	/* prepare before init handlers */
	cmdedit_y = 0;  /* quasireal y, not true if line > xt*yt */
	command_len = 0;
	command_ps = command;
	command[0] = '\0';

	getTermSettings(0, (void *) &initial_settings);
	memcpy(&new_settings, &initial_settings, sizeof(new_settings));
	new_settings.c_lflag &= ~ICANON;        /* unbuffered input */
	/* Turn off echoing and CTRL-C, so we can trap it */
	new_settings.c_lflag &= ~(ECHO | ECHONL | ISIG);
	/* Hmm, in linux c_cc[] is not parsed if ICANON is off */
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	/* Turn off CTRL-C, so we can trap it */
#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE '\0'
#endif
	new_settings.c_cc[VINTR] = _POSIX_VDISABLE;
	setTermSettings(0, (void *) &new_settings);

	/* Now initialize things */
	previous_SIGWINCH_handler = signal(SIGWINCH, win_changed);
	win_changed(0); /* do initial resizing */
#if ENABLE_FEATURE_GETUSERNAME_AND_HOMEDIR
	{
		struct passwd *entry;

		entry = getpwuid(geteuid());
		if (entry) {
			/* If we enter read_line_input for the Nth time,
			 * they may be already allocated! Need to free. */
			free(user_buf);
			if (home_pwd_buf != null_str)
				free(home_pwd_buf);
			user_buf = xstrdup(entry->pw_name);
			home_pwd_buf = xstrdup(entry->pw_dir);
			/* They are not freed on exit (too small to bother) */
		}
	}
#endif
	/* Print out the command prompt */
	parse_prompt(prompt);

	while (1) {
		fflush(stdout);

		if (safe_read(0, &c, 1) < 1) {
			/* if we can't read input then exit */
			goto prepare_to_die;
		}

		ic = c;

#if ENABLE_FEATURE_EDITING_VI
		newdelflag = 1;
		if (vi_cmdmode)
			ic |= vbit;
#endif
		switch (ic) {
		case '\n':
		case '\r':
		vi_case('\n'|vbit:)
		vi_case('\r'|vbit:)
			/* Enter */
			goto_new_line();
			break_out = 1;
			break;
#if ENABLE_FEATURE_EDITING_FANCY_KEYS
		case CTRL('A'):
		vi_case('0'|vbit:)
			/* Control-a -- Beginning of line */
			input_backward(cursor);
			break;
		case CTRL('B'):
		vi_case('h'|vbit:)
		vi_case('\b'|vbit:)
		vi_case('\x7f'|vbit:) /* DEL */
			/* Control-b -- Move back one character */
			input_backward(1);
			break;
#endif
		case CTRL('C'):
		vi_case(CTRL('C')|vbit:)
			/* Control-c -- stop gathering input */
			goto_new_line();
			command_len = 0;
			break_out = -1; /* "do not append '\n'" */
			break;
		case CTRL('D'):
			/* Control-d -- Delete one character, or exit
			 * if the len=0 and no chars to delete */
			if (command_len == 0) {
				errno = 0;
 prepare_to_die:
				/* to control stopped jobs */
				break_out = command_len = -1;
				break;
			}
			input_delete(0);
			break;

#if ENABLE_FEATURE_EDITING_FANCY_KEYS
		case CTRL('E'):
		vi_case('$'|vbit:)
			/* Control-e -- End of line */
			input_end();
			break;
		case CTRL('F'):
		vi_case('l'|vbit:)
		vi_case(' '|vbit:)
			/* Control-f -- Move forward one character */
			input_forward();
			break;
#endif

		case '\b':
		case '\x7f': /* DEL */
			/* Control-h and DEL */
			input_backspace();
			break;

		case '\t':
			input_tab(&lastWasTab);
			break;

#if ENABLE_FEATURE_EDITING_FANCY_KEYS
		case CTRL('K'):
			/* Control-k -- clear to end of line */
			command[cursor] = 0;
			command_len = cursor;
			printf("\033[J");
			break;
		case CTRL('L'):
		vi_case(CTRL('L')|vbit:)
			/* Control-l -- clear screen */
			printf("\033[H");
			redraw(0, command_len - cursor);
			break;
#endif

#if MAX_HISTORY > 0
		case CTRL('N'):
		vi_case(CTRL('N')|vbit:)
		vi_case('j'|vbit:)
			/* Control-n -- Get next command in history */
			if (get_next_history())
				goto rewrite_line;
			break;
		case CTRL('P'):
		vi_case(CTRL('P')|vbit:)
		vi_case('k'|vbit:)
			/* Control-p -- Get previous command from history */
			if ((state->flags & DO_HISTORY) && state->cur_history > 0) {
				get_previous_history();
				goto rewrite_line;
			}
			beep();
			break;
#endif

#if ENABLE_FEATURE_EDITING_FANCY_KEYS
		case CTRL('U'):
		vi_case(CTRL('U')|vbit:)
			/* Control-U -- Clear line before cursor */
			if (cursor) {
				strcpy(command, command + cursor);
				command_len -= cursor;
				redraw(cmdedit_y, command_len);
			}
			break;
#endif
		case CTRL('W'):
		vi_case(CTRL('W')|vbit:)
			/* Control-W -- Remove the last word */
			while (cursor > 0 && isspace(command[cursor-1]))
				input_backspace();
			while (cursor > 0 && !isspace(command[cursor-1]))
				input_backspace();
			break;

#if ENABLE_FEATURE_EDITING_VI
		case 'i'|vbit:
			vi_cmdmode = 0;
			break;
		case 'I'|vbit:
			input_backward(cursor);
			vi_cmdmode = 0;
			break;
		case 'a'|vbit:
			input_forward();
			vi_cmdmode = 0;
			break;
		case 'A'|vbit:
			input_end();
			vi_cmdmode = 0;
			break;
		case 'x'|vbit:
			input_delete(1);
			break;
		case 'X'|vbit:
			if (cursor > 0) {
				input_backward(1);
				input_delete(1);
			}
			break;
		case 'W'|vbit:
			vi_Word_motion(command, 1);
			break;
		case 'w'|vbit:
			vi_word_motion(command, 1);
			break;
		case 'E'|vbit:
			vi_End_motion(command);
			break;
		case 'e'|vbit:
			vi_end_motion(command);
			break;
		case 'B'|vbit:
			vi_Back_motion(command);
			break;
		case 'b'|vbit:
			vi_back_motion(command);
			break;
		case 'C'|vbit:
			vi_cmdmode = 0;
			/* fall through */
		case 'D'|vbit:
			goto clear_to_eol;

		case 'c'|vbit:
			vi_cmdmode = 0;
			/* fall through */
		case 'd'|vbit: {
			int nc, sc;
			sc = cursor;
			prevc = ic;
			if (safe_read(0, &c, 1) < 1)
				goto prepare_to_die;
			if (c == (prevc & 0xff)) {
				/* "cc", "dd" */
				input_backward(cursor);
				goto clear_to_eol;
				break;
			}
			switch (c) {
			case 'w':
			case 'W':
			case 'e':
			case 'E':
				switch (c) {
				case 'w':   /* "dw", "cw" */
					vi_word_motion(command, vi_cmdmode);
					break;
				case 'W':   /* 'dW', 'cW' */
					vi_Word_motion(command, vi_cmdmode);
					break;
				case 'e':   /* 'de', 'ce' */
					vi_end_motion(command);
					input_forward();
					break;
				case 'E':   /* 'dE', 'cE' */
					vi_End_motion(command);
					input_forward();
					break;
				}
				nc = cursor;
				input_backward(cursor - sc);
				while (nc-- > cursor)
					input_delete(1);
				break;
			case 'b':  /* "db", "cb" */
			case 'B':  /* implemented as B */
				if (c == 'b')
					vi_back_motion(command);
				else
					vi_Back_motion(command);
				while (sc-- > cursor)
					input_delete(1);
				break;
			case ' ':  /* "d ", "c " */
				input_delete(1);
				break;
			case '$':  /* "d$", "c$" */
			clear_to_eol:
				while (cursor < command_len)
					input_delete(1);
				break;
			}
			break;
		}
		case 'p'|vbit:
			input_forward();
			/* fallthrough */
		case 'P'|vbit:
			put();
			break;
		case 'r'|vbit:
			if (safe_read(0, &c, 1) < 1)
				goto prepare_to_die;
			if (c == 0)
				beep();
			else {
				*(command + cursor) = c;
				putchar(c);
				putchar('\b');
			}
			break;
#endif /* FEATURE_COMMAND_EDITING_VI */

		case '\x1b': /* ESC */

#if ENABLE_FEATURE_EDITING_VI
			if (state->flags & VI_MODE) {
				/* ESC: insert mode --> command mode */
				vi_cmdmode = 1;
				input_backward(1);
				break;
			}
#endif
			/* escape sequence follows */
			if (safe_read(0, &c, 1) < 1)
				goto prepare_to_die;
			/* different vt100 emulations */
			if (c == '[' || c == 'O') {
		vi_case('['|vbit:)
		vi_case('O'|vbit:)
				if (safe_read(0, &c, 1) < 1)
					goto prepare_to_die;
			}
			if (c >= '1' && c <= '9') {
				unsigned char dummy;

				if (safe_read(0, &dummy, 1) < 1)
					goto prepare_to_die;
				if (dummy != '~')
					c = '\0';
			}

			switch (c) {
#if ENABLE_FEATURE_TAB_COMPLETION
			case '\t':                      /* Alt-Tab */
				input_tab(&lastWasTab);
				break;
#endif
#if MAX_HISTORY > 0
			case 'A':
				/* Up Arrow -- Get previous command from history */
				if ((state->flags & DO_HISTORY) && state->cur_history > 0) {
					get_previous_history();
					goto rewrite_line;
				}
				beep();
				break;
			case 'B':
				/* Down Arrow -- Get next command in history */
				if (!get_next_history())
					break;
 rewrite_line:
				/* Rewrite the line with the selected history item */
				/* change command */
				command_len = strlen(strcpy(command, state->history[state->cur_history]));
				/* redraw and go to eol (bol, in vi */
				redraw(cmdedit_y, (state->flags & VI_MODE) ? 9999 : 0);
				break;
#endif
			case 'C':
				/* Right Arrow -- Move forward one character */
				input_forward();
				break;
			case 'D':
				/* Left Arrow -- Move back one character */
				input_backward(1);
				break;
			case '3':
				/* Delete */
				input_delete(0);
				break;
			case '1': // vt100? linux vt? or what?
			case '7': // vt100? linux vt? or what?
			case 'H': /* xterm's <Home> */
				input_backward(cursor);
				break;
			case '4': // vt100? linux vt? or what?
			case '8': // vt100? linux vt? or what?
			case 'F': /* xterm's <End> */
				input_end();
				break;
			default:
				c = '\0';
				beep();
			}
			break;

		default:        /* If it's regular input, do the normal thing */
#if ENABLE_FEATURE_NONPRINTABLE_INVERSE_PUT
			/* Control-V -- Add non-printable symbol */
			if (c == CTRL('V')) {
				if (safe_read(0, &c, 1) < 1)
					goto prepare_to_die;
				if (c == 0) {
					beep();
					break;
				}
			} else
#endif

#if ENABLE_FEATURE_EDITING_VI
			if (vi_cmdmode)  /* Don't self-insert */
				break;
#endif
			if (!Isprint(c)) /* Skip non-printable characters */
				break;

			if (command_len >= (maxsize - 2))        /* Need to leave space for enter */
				break;

			command_len++;
			if (cursor == (command_len - 1)) {      /* Append if at the end of the line */
				command[cursor] = c;
				command[cursor+1] = '\0';
				cmdedit_set_out_char(' ');
			} else {                        /* Insert otherwise */
				int sc = cursor;

				memmove(command + sc + 1, command + sc, command_len - sc);
				command[sc] = c;
				sc++;
				/* rewrite from cursor */
				input_end();
				/* to prev x pos + 1 */
				input_backward(cursor - sc);
			}
			break;
		}
		if (break_out)                  /* Enter is the command terminator, no more input. */
			break;

		if (c != '\t')
			lastWasTab = FALSE;
	}