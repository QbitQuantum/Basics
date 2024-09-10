void GetstrLC(char *sStr, int iMaxlen)
{
    unsigned char   ch = 0;
    int		    iPos = 0;

    strcpy(sStr, "");
    alarm_on();

    while (ch != 13) {

	ch = Readkey();

	if ((ch == 8) || (ch == KEY_DEL) || (ch == 127)) {
	    if (iPos > 0) {
		BackErase();
		sStr[--iPos] = '\0';
	    } else {
		Beep();
	    }
	}

	if ((ch > 31 && ch < 127) || traduce((char *)&ch)) {
	    if (iPos <= iMaxlen) {
		iPos++;
		snprintf(sStr + strlen(sStr), 5, "%c", ch);
		PUTCHAR(ch);
	    } else {
		Beep();
	    }
	}
    }

    Enter(1);
}