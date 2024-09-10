int
run(void) {
	char buf[32];
	char c;
	FILE *f;
	int n;

	while(1) {
		read(0, &c, 1);
		memset(buf, '\0', sizeof buf);
		buf[0]=c;
		switch_top:
		switch(c) {
		case CONTROL('['):
			read(0, &c, 1);
			esc_switch_top:
			switch(c) {
				case CONTROL('['): /* ESC, need to press twice due to console limitations */
					c=CONTROL('C');
					goto switch_top;
				case '[':
					read(0, &c, 1);
					switch(c) {
						case '1': /* Home */
						case '7':
						case 'H':
							if(c!='H') read(0, &c, 1); /* Remove trailing '~' from stdin */
							c=CONTROL('A');
							goto switch_top;
						case '2': /* Insert */
							read(0, &c, 1); /* Remove trailing '~' from stdin */
							c=CONTROL('Y');
							goto switch_top;
						case '3': /* Delete */
							read(0, &c, 1); /* Remove trailing '~' from stdin */
							c=CONTROL('D');
							goto switch_top;
						case '4': /* End */
						case '8':
						case 'F':
							if(c!='F') read(0, &c, 1); /* Remove trailing '~' from stdin */
							c=CONTROL('E');
							goto switch_top;
						case '5': /* PageUp */
							read(0, &c, 1); /* Remove trailing '~' from stdin */
							c=CONTROL('V');
							goto switch_top;
						case '6': /* PageDown */
							read(0, &c, 1); /* Remove trailing '~' from stdin */
							c='v';
							goto esc_switch_top;
						case 'A': /* Up arrow */
							c=CONTROL('P');
							goto switch_top;
						case 'B': /* Down arrow */
							c=CONTROL('N');
							goto switch_top;
						case 'C': /* Right arrow */
							c=CONTROL('F');
							goto switch_top;
						case 'D': /* Left arrow */
							c=CONTROL('B');
							goto switch_top;
					}
					break;
				case 'b':
					while(cursor > 0 && text[nextrune(-1)] == ' ')
						cursor = nextrune(-1);
					while(cursor > 0 && text[nextrune(-1)] != ' ')
						cursor = nextrune(-1);
					break;
				case 'f':
					while(text[cursor] != '\0' && text[nextrune(+1)] == ' ')
						cursor = nextrune(+1);
					if(text[cursor] != '\0') do
						cursor = nextrune(+1);
					while(text[cursor] != '\0' && text[cursor] != ' ');
					break;
				case 'd':
					while(text[cursor] != '\0' && text[nextrune(+1)] == ' ') {
						cursor = nextrune(+1);
						insert(NULL, nextrune(-1) - cursor);
					}
					if(text[cursor] != '\0') do {
						cursor = nextrune(+1);
						insert(NULL, nextrune(-1) - cursor);
					} while(text[cursor] != '\0' && text[cursor] != ' ');
					break;
				case 'v':
					if(!next)
						break;
					sel=curr=next;
					calcoffsets();
					break;
				default:
					break;
			}
			break;
		case CONTROL('C'):
			return EXIT_FAILURE;
		case CONTROL('M'): /* Return */
		case CONTROL('J'):
			if(sel) strncpy(text, sel->text, sizeof text); /* Complete the input first, when hitting return */
			cursor = strlen(text);
			match(TRUE);
			drawmenu();
			/* fallthrough */
		case CONTROL(']'):
		case CONTROL('\\'): /* These are usually close enough to RET to replace Shift+RET, again due to console limitations */
			puts(text);
			return EXIT_SUCCESS;
		case CONTROL('A'):
			if(sel == matches) {
				cursor=0;
				break;
			}
			sel=curr=matches;
			calcoffsets();
			break;
		case CONTROL('E'):
			if(text[cursor] != '\0') {
				cursor = strlen(text);
				break;
			}
			if(next) {
				curr = matchend;
				calcoffsets();
				curr = prev;
				calcoffsets();
				while(next && (curr = curr->right))
					calcoffsets();
			}
			sel = matchend;
			break;
		case CONTROL('B'):
			if(cursor > 0 && (!sel || !sel->left || lines > 0)) {
				cursor = nextrune(-1);
				break;
			}
			/* fallthrough */
		case CONTROL('P'):
			if(sel && sel->left && (sel = sel->left)->right == curr) {
				curr = prev;
				calcoffsets();
			}
			break;
		case CONTROL('F'):
			if(text[cursor] != '\0') {
				cursor = nextrune(+1);
				break;
			}
			/* fallthrough */
		case CONTROL('N'):
			if(sel && sel->right && (sel = sel->right) == next) {
				curr = next;
				calcoffsets();
			}
			break;
		case CONTROL('D'):
			if(text[cursor] == '\0')
				break;
			cursor = nextrune(+1);
			/* fallthrough */
		case CONTROL('H'):
		case CONTROL('?'): /* Backspace */
			if(cursor == 0)
				break;
			insert(NULL, nextrune(-1) - cursor);
			break;
		case CONTROL('I'): /* TAB */
			if(!sel)
				break;
			strncpy(text, sel->text, sizeof text);
			cursor = strlen(text);
			match(TRUE);
			break;
		case CONTROL('K'):
			text[cursor] = '\0';
			match(FALSE);
			break;
		case CONTROL('U'):
			insert(NULL, 0 - cursor);
			break;
		case CONTROL('W'):
			while(cursor > 0 && text[nextrune(-1)] == ' ')
				insert(NULL, nextrune(-1) - cursor);
			while(cursor > 0 && text[nextrune(-1)] != ' ')
				insert(NULL, nextrune(-1) - cursor);
			break;
		case CONTROL('V'):
			if(!prev)
				break;
			sel = curr = prev;
			calcoffsets();
			break;
		case CONTROL('Y'):
			if((f=popen(XSEL, "r")) != NULL) {
				while((n= fread(&buf, 1, sizeof buf, f)) > 0) insert(buf, n);
				pclose(f);
			}
		default:
			if(!iscntrl(*buf))
				insert(buf, strlen(buf));
			break;
		}
		drawmenu();
	}
}