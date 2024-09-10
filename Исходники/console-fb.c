static void console_fb_write_byte(struct console_fb_data_t * dat, unsigned char c)
{
	u32_t cp;
	char * rest;
	int t;

	switch(dat->state)
	{
	case ESC_STATE_NORMAL:
		switch(c)
		{
		case '\e':	/* ESC state */
			dat->state = ESC_STATE_ESC;
			break;

		default:
			dat->utf8[dat->usize++] = c;
			if(utf8_to_ucs4(&cp, 1, (const char *)dat->utf8, dat->usize, (const char **)&rest) > 0)
			{
				dat->usize -= rest - dat->utf8;
				memmove(dat->utf8, rest, dat->usize);
				console_fb_putcode(dat, cp);
			}
			break;
		}
		break;

	case ESC_STATE_ESC:
		switch(c)
		{
		case 'c':	/* Reset */
			console_fb_show_cursor(dat, 1);
			console_fb_set_color_bright(dat, 0);
			console_fb_set_color(dat, TCOLOR_WHITE, TCOLOR_BLACK);
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'D':	/* Scroll display down one line */
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'M':	/* Scroll display up one line */
			dat->state = ESC_STATE_NORMAL;
			break;

		case '7':	/* Save cursor position and attrs */
			console_fb_save_cursor(dat);
			console_fb_save_color(dat);
			dat->state = ESC_STATE_NORMAL;
			break;

		case '8':	/* Restore cursor position and attrs */
			console_fb_restore_cursor(dat);
			console_fb_restore_color(dat);
			dat->state = ESC_STATE_NORMAL;
			break;

		case '[':	/* CSI codes */
			dat->csize = 0;
			dat->abuf[0] = 0;
			dat->asize = 0;
			dat->state = ESC_STATE_CSI;
			break;

		default:
			dat->state = ESC_STATE_NORMAL;
			break;
		}
		break;

	case ESC_STATE_CSI:
		dat->cbuf[dat->csize++] = c;

		switch(dat->cbuf[dat->csize - 1])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			dat->abuf[dat->asize] *= 10;
			dat->abuf[dat->asize] += (dat->cbuf[dat->csize - 1] - '0');
			break;

		case ';':
			dat->asize++;
			dat->abuf[dat->asize] = 0;
			break;

		case 'A':	/* Move the cursor up */
			t = dat->abuf[0];
			t = (t) ? t : 1;
			console_fb_cursor_gotoxy(dat, dat->x, dat->y - t);
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'B':	/* Move the cursor down */
			t = dat->abuf[0];
			t = (t) ? t : 1;
			console_fb_cursor_gotoxy(dat, dat->x, dat->y + t);
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'C':	/* Move the cursor right */
			t = dat->abuf[0];
			t = (t) ? t : 1;
			console_fb_cursor_gotoxy(dat, dat->x + t, dat->y);
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'D':	/* Move the cursor left */
			t = dat->abuf[0];
			t = (t) ? t : 1;
			console_fb_cursor_gotoxy(dat, dat->x - t, dat->y);
			dat->state = ESC_STATE_NORMAL;
			break;

		case 's':	/* Save cursor position */
			console_fb_save_cursor(dat);
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'u':	/* Restore cursor position */
			console_fb_restore_cursor(dat);
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'J':	/* Clear the screen */
			console_fb_clear_screen(dat);
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'H':	/* Cursor home */
		case 'f':	/* Force cursor position */
			if(dat->asize == 0)
				console_fb_cursor_gotoxy(dat, 0, dat->y);
			else
				console_fb_cursor_gotoxy(dat, dat->abuf[1], dat->abuf[0]);
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'c':		/* Request terminal Type */
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'n':
			switch(dat->abuf[0])
			{
			case 5:		/* Request terminal status */
				break;
			case 6:		/* Request cursor position */
				break;
			};
			dat->state = ESC_STATE_NORMAL;
			break;

		case 'm':		/* Set Display Attributes */
			for(t = 0; t <= dat->asize; t++)
			{
				switch(dat->abuf[t])
				{
				case 0:		/* Reset all attrs */
					console_fb_set_color_bright(dat, 0);
					console_fb_set_color(dat, TCOLOR_WHITE, TCOLOR_BLACK);
					break;
				case 1:		/* Bright */
					console_fb_set_color_bright(dat, 1);
					console_fb_set_color(dat, dat->f, dat->b);
					break;
				case 2:		/* Dim */
					break;
				case 4:		/* Underscore */
					break;
				case 5:		/* Blink */
					break;
				case 7:		/* Reverse */
					console_fb_set_color(dat, dat->b, dat->f);
					break;
				case 8:		/* Hidden */
					break;

				case 30:	/* Set foreground color */
				case 31:
				case 32:
				case 33:
				case 34:
				case 35:
				case 36:
				case 37:
					console_fb_set_color(dat, dat->abuf[t] - 30, dat->b);
					break;

				case 40:	/* Set background color */
				case 41:
				case 42:
				case 43:
				case 44:
				case 45:
				case 46:
				case 47:
					console_fb_set_color(dat, dat->f, dat->abuf[t] - 40);
					break;

				default:
					break;
				}
			}
			dat->state = ESC_STATE_NORMAL;
			break;

		default:
			dat->state = ESC_STATE_NORMAL;
			break;
		}
		break;

	default:
		dat->state = ESC_STATE_NORMAL;
		break;
	}
}