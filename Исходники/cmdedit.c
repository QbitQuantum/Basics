int cmdedit_read_input(char *prompt, char command[BUFSIZ])
{
	int break_out = 0;
	int lastWasTab = FALSE;
	unsigned char c;
	unsigned int ic;
#if ENABLE_FEATURE_COMMAND_EDITING_VI
	unsigned int prevc;
	int vi_cmdmode = 0;
#endif
	/* prepare before init handlers */
	cmdedit_y = 0;  /* quasireal y, not true work if line > xt*yt */
	len = 0;
	command_ps = command;

	getTermSettings(0, (void *) &initial_settings);
	memcpy(&new_settings, &initial_settings, sizeof(struct termios));
	new_settings.c_lflag &= ~ICANON;        /* unbuffered input */
	/* Turn off echoing and CTRL-C, so we can trap it */
	new_settings.c_lflag &= ~(ECHO | ECHONL | ISIG);
	/* Hmm, in linux c_cc[] not parsed if set ~ICANON */
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	/* Turn off CTRL-C, so we can trap it */
#	ifndef _POSIX_VDISABLE
#       	define _POSIX_VDISABLE '\0'
#	endif
	new_settings.c_cc[VINTR] = _POSIX_VDISABLE;
	command[0] = 0;

	setTermSettings(0, (void *) &new_settings);
	handlers_sets |= SET_RESET_TERM;

	/* Now initialize things */
	cmdedit_init();
	/* Print out the command prompt */
	parse_prompt(prompt);

	while (1) {
		fflush(stdout);                 /* buffered out to fast */

		if (safe_read(0, &c, 1) < 1)
			/* if we can't read input then exit */
			goto prepare_to_die;

		ic = c;

#if ENABLE_FEATURE_COMMAND_EDITING_VI
		newdelflag = 1;
		if (vi_cmdmode)
			ic |= vbit;
#endif
		switch (ic) {
		case '\n':
		case '\r':
		vi_case( case '\n'|vbit: )
		vi_case( case '\r'|vbit: )
			/* Enter */
			goto_new_line();
			break_out = 1;
			break;
		case CNTRL('A'):
		vi_case( case '0'|vbit: )
			/* Control-a -- Beginning of line */
			input_backward(cursor);
			break;
		case CNTRL('B'):
		vi_case( case 'h'|vbit: )
		vi_case( case '\b'|vbit: )
		vi_case( case DEL|vbit: )
			/* Control-b -- Move back one character */
			input_backward(1);
			break;
		case CNTRL('C'):
		vi_case( case CNTRL('C')|vbit: )
			/* Control-c -- stop gathering input */
			goto_new_line();
#if !ENABLE_ASH
			command[0] = 0;
			len = 0;
			lastWasTab = FALSE;
			put_prompt();
#else
			len = 0;
			break_out = -1; /* to control traps */
#endif
			break;
		case CNTRL('D'):
			/* Control-d -- Delete one character, or exit
			 * if the len=0 and no chars to delete */
			if (len == 0) {
				errno = 0;
 prepare_to_die:
#if !ENABLE_ASH
				printf("exit");
				goto_new_line();
				/* cmdedit_reset_term() called in atexit */
				exit(EXIT_SUCCESS);
#else
				/* to control stopped jobs */
				len = break_out = -1;
				break;
#endif
			} else {
				input_delete(0);
			}
			break;
		case CNTRL('E'):
		vi_case( case '$'|vbit: )
			/* Control-e -- End of line */
			input_end();
			break;
		case CNTRL('F'):
		vi_case( case 'l'|vbit: )
		vi_case( case ' '|vbit: )
			/* Control-f -- Move forward one character */
			input_forward();
			break;
		case '\b':
		case DEL:
			/* Control-h and DEL */
			input_backspace();
			break;
		case '\t':
#if ENABLE_FEATURE_COMMAND_TAB_COMPLETION
			input_tab(&lastWasTab);
#endif
			break;
		case CNTRL('K'):
			/* Control-k -- clear to end of line */
			command[cursor] = 0;
			len = cursor;
			printf("\033[J");
			break;
		case CNTRL('L'):
		vi_case( case CNTRL('L')|vbit: )
			/* Control-l -- clear screen */
			printf("\033[H");
			redraw(0, len - cursor);
			break;
#if MAX_HISTORY > 0
		case CNTRL('N'):
		vi_case( case CNTRL('N')|vbit: )
		vi_case( case 'j'|vbit: )
			/* Control-n -- Get next command in history */
			if (get_next_history())
				goto rewrite_line;
			break;
		case CNTRL('P'):
		vi_case( case CNTRL('P')|vbit: )
		vi_case( case 'k'|vbit: )
			/* Control-p -- Get previous command from history */
			if (cur_history > 0) {
				get_previous_history();
				goto rewrite_line;
			} else {
				beep();
			}
			break;
#endif
		case CNTRL('U'):
		vi_case( case CNTRL('U')|vbit: )
			/* Control-U -- Clear line before cursor */
			if (cursor) {
				strcpy(command, command + cursor);
				redraw(cmdedit_y, len -= cursor);
			}
			break;
		case CNTRL('W'):
		vi_case( case CNTRL('W')|vbit: )
			/* Control-W -- Remove the last word */
			while (cursor > 0 && isspace(command[cursor-1]))
				input_backspace();
			while (cursor > 0 &&!isspace(command[cursor-1]))
				input_backspace();
			break;
#if ENABLE_FEATURE_COMMAND_EDITING_VI
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
				while (cursor < len)
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

		case ESC:

#if ENABLE_FEATURE_COMMAND_EDITING_VI
			if (vi_mode) {
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
		vi_case( case '['|vbit: )
		vi_case( case 'O'|vbit: )
				if (safe_read(0, &c, 1) < 1)
					goto prepare_to_die;
			}
			if (c >= '1' && c <= '9') {
				unsigned char dummy;

				if (safe_read(0, &dummy, 1) < 1)
					goto prepare_to_die;
				if (dummy != '~')
					c = 0;
			}
			switch (c) {
#if ENABLE_FEATURE_COMMAND_TAB_COMPLETION
			case '\t':                      /* Alt-Tab */

				input_tab(&lastWasTab);
				break;
#endif
#if MAX_HISTORY > 0
			case 'A':
				/* Up Arrow -- Get previous command from history */
				if (cur_history > 0) {
					get_previous_history();
					goto rewrite_line;
				} else {
					beep();
				}
				break;
			case 'B':
				/* Down Arrow -- Get next command in history */
				if (!get_next_history())
					break;
				/* Rewrite the line with the selected history item */
rewrite_line:
				/* change command */
				len = strlen(strcpy(command, history[cur_history]));
				/* redraw and go to eol (bol, in vi */
#if ENABLE_FEATURE_COMMAND_EDITING_VI
				redraw(cmdedit_y, vi_mode ? 9999:0);
#else
				redraw(cmdedit_y, 0);
#endif
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
			case '1':
			case 'H':
				/* <Home> */
				input_backward(cursor);
				break;
			case '4':
			case 'F':
				/* <End> */
				input_end();
				break;
			default:
				c = 0;
				beep();
			}
			break;

		default:        /* If it's regular input, do the normal thing */
#if ENABLE_FEATURE_NONPRINTABLE_INVERSE_PUT
			/* Control-V -- Add non-printable symbol */
			if (c == CNTRL('V')) {
				if (safe_read(0, &c, 1) < 1)
					goto prepare_to_die;
				if (c == 0) {
					beep();
					break;
				}
			} else
#endif
			{
#if ENABLE_FEATURE_COMMAND_EDITING_VI
				if (vi_cmdmode)  /* don't self-insert */
					break;
#endif
				if (!Isprint(c)) /* Skip non-printable characters */
					break;
			}

			if (len >= (BUFSIZ - 2))        /* Need to leave space for enter */
				break;

			len++;

			if (cursor == (len - 1)) {      /* Append if at the end of the line */
				*(command + cursor) = c;
				*(command + cursor + 1) = 0;
				cmdedit_set_out_char(0);
			} else {                        /* Insert otherwise */
				int sc = cursor;

				memmove(command + sc + 1, command + sc, len - sc);
				*(command + sc) = c;
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