int console_readkey(void)
{
    unsigned char ch;
    int num;

    GETCHAR(ch);

    switch (ch) {
	case VKEY_ESC:
	    GETCHAR(ch);
	    switch (ch) {
		case 'O':
		    GETCHAR(ch);
		    switch (ch) {
			case 'P':
			    return VKEY_F1;
			case 'Q':
			    return VKEY_F2;
			case 'R':
			    return VKEY_F3;
			case 'S':
			    return VKEY_F4;
			}
		    return (int)ch;

		case '[':
		    GETCHAR(ch);
		    if ((ch >= '0') && (ch <= '9')) {
			console_readnum(&num,&ch);
			if (ch == '~') {
			    switch (num) {
				case 2:
				    return VKEY_HOME;
				case 3:
				    return VKEY_PGUP;
				case 5:
				    if (console_mode == XTERM) return VKEY_PGUP;
				    return VKEY_END;
				case 6:
				    if (console_mode == XTERM) return VKEY_PGDN;
				    return VKEY_PGDN;
				case 11:
				    return VKEY_F1;
				case 12:
				    return VKEY_F2;
				case 13:
				    return VKEY_F3;
				case 14:
				    return VKEY_F4;
				case 15:
				    return VKEY_F5;
				case 17:
				    return VKEY_F6;
				case 18:
				    return VKEY_F7;
				case 19:
				    return VKEY_F8;
				case 20:
				    return VKEY_F9;
				case 21:
				    return VKEY_F10;
				case 23:
				    return VKEY_F11;
				case 24:
				    return VKEY_F12;
				}
			    return (int)ch;
			    }
			}
		    else {
			switch (ch) {
			    case 'A':
				return VKEY_UP;
			    case 'B':
				return VKEY_DOWN;
			    case 'C':
				return VKEY_RIGHT;
			    case 'D':
				return VKEY_LEFT;
			    case 'F':
				return VKEY_HOME;
			    case 'H':
				return VKEY_END;
			    default:
				return (int) ch;
			    }
			}
		default:
		    return (int)ch;
	
		}
	default:
	    return (int) ch;
	}
}