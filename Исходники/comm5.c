yylex()
{
	register c;
	int i;

	if (pass == PASS_1) {
		/* scan the input file */
		do
			c = nextchar();
		while (isspace(c) && c != '\n');
		if (ISALPHA(c))
			c = inident(c);
		else if (isdigit(c))
			c = innumber(c);
		else switch (c) {
		case '=':
		case '<':
		case '>':
		case '|':
		case '&':
			c = induo(c); break;
		case ASC_SQUO:
		case ASC_DQUO:
			c = instring(c); break;
		case ASC_COMM:
			do
				c = nextchar();
			while (c != '\n' && c != '\0');
			break;
		case CTRL('A'):
			c = CODE1; readcode(1); break;
		case CTRL('B'):
			c = CODE2; readcode(2); break;
		case CTRL('C'):
			c = CODE4; readcode(4); break;
		}

		/* produce the intermediate token file */
		if (c <= 0)
			return(0);
		if (c <= 127)
			putc(c, tempfile);
		else
			putval(c);
	} else {
		/* read from intermediate token file */
		c = getc(tempfile);
		if (c == EOF)
			return(0);
		if (c > 127) {
			c += 128;
			c = getval(c);
		}
	}
	return(c);
}