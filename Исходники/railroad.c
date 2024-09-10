static void
ShowSign(char *string)
{
    char *base = string;
    int ch, first, last;

    if (moveit != 0) {
	tputs(tgoto(moveit, 0, height - 1), 1, outc);
	tputs(wipeit, 1, outc);
    }

    while (*string != 0) {
	ch = *string;
	if (ch != ' ') {
	    if (moveit != 0) {
		for (first = length - 2; first >= (string - base); first--) {
		    if (first < length - 1) {
			tputs(tgoto(moveit, first + 1, height - 1), 1, outc);
			PutChar(' ');
		    }
		    tputs(tgoto(moveit, first, height - 1), 1, outc);
		    PutChar(ch);
		}
	    } else {
		last = ch;
		if (isalpha(ch)) {
		    first = isupper(ch) ? 'A' : 'a';
		} else if (isdigit(ch)) {
		    first = '0';
		} else {
		    first = ch;
		}
		if (first < last) {
		    Underline(1);
		    while (first < last) {
			PutChar(first);
			Backup();
			first++;
		    }
		    Underline(0);
		}
	    }
	    if (moveit != 0)
		Backup();
	}
	StandOut(1);
	PutChar(ch);
	StandOut(0);
	fflush(stdout);
	string++;
    }
    if (moveit != 0)
	tputs(wipeit, 1, outc);
    putchar('\n');
}