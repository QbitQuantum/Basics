/*
 * unvis - decode characters previously encoded by vis
 */
int
unvis(char *cp, int c, int *astate, int flag)
{
	unsigned char uc = (unsigned char)c;
	unsigned char st, ia, is, lc;

/*
 * Bottom 8 bits of astate hold the state machine state.
 * Top 8 bits hold the current character in the http 1866 nv string decoding
 */
#define GS(a)		((a) & 0xff)
#define SS(a, b)	(((uint32_t)(a) << 24) | (b))
#define GI(a)		((uint32_t)(a) >> 24)

	_DIAGASSERT(cp != NULL);
	_DIAGASSERT(astate != NULL);
	st = GS(*astate);

	if (flag & UNVIS_END) {
		switch (st) {
		case S_OCTAL2:
		case S_OCTAL3:
		case S_HEX2:
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case S_GROUND:
			return UNVIS_NOCHAR;
		default:
			return UNVIS_SYNBAD;
		}
	}

	switch (st) {

	case S_GROUND:
		*cp = 0;
		if ((flag & VIS_NOESCAPE) == 0 && c == '\\') {
			*astate = SS(0, S_START);
			return UNVIS_NOCHAR;
		}
		if ((flag & VIS_HTTP1808) && c == '%') {
			*astate = SS(0, S_HEX1);
			return UNVIS_NOCHAR;
		}
		if ((flag & VIS_HTTP1866) && c == '&') {
			*astate = SS(0, S_AMP);
			return UNVIS_NOCHAR;
		}
		if ((flag & VIS_MIMESTYLE) && c == '=') {
			*astate = SS(0, S_MIME1);
			return UNVIS_NOCHAR;
		}
		*cp = c;
		return UNVIS_VALID;

	case S_START:
		switch(c) {
		case '\\':
			*cp = c;
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			*cp = (c - '0');
			*astate = SS(0, S_OCTAL2);
			return UNVIS_NOCHAR;
		case 'M':
			*cp = (char)0200;
			*astate = SS(0, S_META);
			return UNVIS_NOCHAR;
		case '^':
			*astate = SS(0, S_CTRL);
			return UNVIS_NOCHAR;
		case 'n':
			*cp = '\n';
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case 'r':
			*cp = '\r';
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case 'b':
			*cp = '\b';
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case 'a':
			*cp = '\007';
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case 'v':
			*cp = '\v';
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case 't':
			*cp = '\t';
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case 'f':
			*cp = '\f';
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case 's':
			*cp = ' ';
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case 'E':
			*cp = '\033';
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		case 'x':
			*astate = SS(0, S_HEX);
			return UNVIS_NOCHAR;
		case '\n':
			/*
			 * hidden newline
			 */
			*astate = SS(0, S_GROUND);
			return UNVIS_NOCHAR;
		case '$':
			/*
			 * hidden marker
			 */
			*astate = SS(0, S_GROUND);
			return UNVIS_NOCHAR;
		}
		goto bad;

	case S_META:
		if (c == '-')
			*astate = SS(0, S_META1);
		else if (c == '^')
			*astate = SS(0, S_CTRL);
		else 
			goto bad;
		return UNVIS_NOCHAR;

	case S_META1:
		*astate = SS(0, S_GROUND);
		*cp |= c;
		return UNVIS_VALID;

	case S_CTRL:
		if (c == '?')
			*cp |= 0177;
		else
			*cp |= c & 037;
		*astate = SS(0, S_GROUND);
		return UNVIS_VALID;

	case S_OCTAL2:	/* second possible octal digit */
		if (isoctal(uc)) {
			/*
			 * yes - and maybe a third
			 */
			*cp = (*cp << 3) + (c - '0');
			*astate = SS(0, S_OCTAL3);
			return UNVIS_NOCHAR;
		}
		/*
		 * no - done with current sequence, push back passed char
		 */
		*astate = SS(0, S_GROUND);
		return UNVIS_VALIDPUSH;

	case S_OCTAL3:	/* third possible octal digit */
		*astate = SS(0, S_GROUND);
		if (isoctal(uc)) {
			*cp = (*cp << 3) + (c - '0');
			return UNVIS_VALID;
		}
		/*
		 * we were done, push back passed char
		 */
		return UNVIS_VALIDPUSH;

	case S_HEX:
		if (!isxdigit(uc))
			goto bad;
		/*FALLTHROUGH*/
	case S_HEX1:
		if (isxdigit(uc)) {
			*cp = xtod(uc);
			*astate = SS(0, S_HEX2);
			return UNVIS_NOCHAR;
		}
		/*
		 * no - done with current sequence, push back passed char
		 */
		*astate = SS(0, S_GROUND);
		return UNVIS_VALIDPUSH;

	case S_HEX2:
		*astate = S_GROUND;
		if (isxdigit(uc)) {
			*cp = xtod(uc) | (*cp << 4);
			return UNVIS_VALID;
		}
		return UNVIS_VALIDPUSH;

	case S_MIME1:
		if (uc == '\n' || uc == '\r') {
			*astate = SS(0, S_EATCRNL);
			return UNVIS_NOCHAR;
		}
		if (isxdigit(uc) && (isdigit(uc) || isupper(uc))) {
			*cp = XTOD(uc);
			*astate = SS(0, S_MIME2);
			return UNVIS_NOCHAR;
		}
		goto bad;

	case S_MIME2:
		if (isxdigit(uc) && (isdigit(uc) || isupper(uc))) {
			*astate = SS(0, S_GROUND);
			*cp = XTOD(uc) | (*cp << 4);
			return UNVIS_VALID;
		}
		goto bad;

	case S_EATCRNL:
		switch (uc) {
		case '\r':
		case '\n':
			return UNVIS_NOCHAR;
		case '=':
			*astate = SS(0, S_MIME1);
			return UNVIS_NOCHAR;
		default:
			*cp = uc;
			*astate = SS(0, S_GROUND);
			return UNVIS_VALID;
		}

	case S_AMP:
		*cp = 0;
		if (uc == '#') {
			*astate = SS(0, S_NUMBER);
			return UNVIS_NOCHAR;
		}
		*astate = SS(0, S_STRING);
		/*FALLTHROUGH*/

	case S_STRING:
		ia = *cp;		/* index in the array */
		is = GI(*astate);	/* index in the string */
		lc = is == 0 ? 0 : nv[ia].name[is - 1];	/* last character */

		if (uc == ';')
			uc = '\0';

		for (; ia < __arraycount(nv); ia++) {
			if (is != 0 && nv[ia].name[is - 1] != lc)
				goto bad;
			if (nv[ia].name[is] == uc)
				break;
		}

		if (ia == __arraycount(nv))
			goto bad;

		if (uc != 0) {
			*cp = ia;
			*astate = SS(is + 1, S_STRING);
			return UNVIS_NOCHAR;
		}

		*cp = nv[ia].value;
		*astate = SS(0, S_GROUND);
		return UNVIS_VALID;

	case S_NUMBER:
		if (uc == ';')
			return UNVIS_VALID;
		if (!isdigit(uc))
			goto bad;
		*cp += (*cp * 10) + uc - '0';
		return UNVIS_NOCHAR;

	default:
	bad:
		/*
		 * decoder in unknown state - (probably uninitialized)
		 */
		*astate = SS(0, S_GROUND);
		return UNVIS_SYNBAD;
	}
}