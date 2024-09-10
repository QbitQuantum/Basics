/*
 * y_entries:
 *	find the yacc tags and put them in.
 */
void
y_entries(void)
{
	int	c;
	char	*sp;
	bool	in_rule;
	char	tok[MAXTOKEN];

	in_rule = NO;

	while (GETC(!=, EOF))
		switch (c) {
		case '\n':
			SETLINE;
			/* FALLTHROUGH */
		case ' ':
		case '\f':
		case '\r':
		case '\t':
			break;
		case '{':
			if (skip_key('}'))
				in_rule = NO;
			break;
		case '\'':
		case '"':
			if (skip_key(c))
				in_rule = NO;
			break;
		case '%':
			if (GETC(==, '%'))
				return;
			(void)ungetc(c, inf);
			break;
		case '/':
			if (GETC(==, '*') || c == '/')
				skip_comment(c);
			else
				(void)ungetc(c, inf);
			break;
		case '|':
		case ';':
			in_rule = NO;
			break;
		default:
			if (in_rule || (!isalpha(c) && c != '.' && c != '_'))
				break;
			sp = tok;
			*sp++ = c;
			while (GETC(!=, EOF) && (intoken(c) || c == '.'))
				*sp++ = c;
			*sp = EOS;
			getline();		/* may change before ':' */
			while (iswhite(c)) {
				if (c == '\n')
					SETLINE;
				if (GETC(==, EOF))
					return;
			}
			if (c == ':') {
				pfnote(tok, lineno);
				in_rule = YES;
			}
			else
				(void)ungetc(c, inf);
		}