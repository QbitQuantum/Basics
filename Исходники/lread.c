l_R(int poststar, int reqint)
#endif
{
	char s[FMAX+EXPMAXDIGS+4];
	register int ch;
	register char *sp, *spe, *sp1;
	long e, exp;
	int havenum, havestar, se;

	if (!poststar) {
		if (f__lcount > 0)
			return(0);
		f__lcount = 1;
		}
#ifdef Allow_TYQUAD
	f__llx = 0;
#endif
	f__ltype = 0;
	exp = 0;
	havestar = 0;
retry:
	sp1 = sp = s;
	spe = sp + FMAX;
	havenum = 0;

	switch(GETC(ch)) {
		case '-': *sp++ = ch; sp1++; spe++;
		case '+':
			GETC(ch);
		}
	while(ch == '0') {
		++havenum;
		GETC(ch);
		}
	while(isdigit(ch)) {
		if (sp < spe) *sp++ = ch;
		else ++exp;
		GETC(ch);
		}
	if (ch == '*' && !poststar) {
		if (sp == sp1 || exp || *s == '-') {
			errfl(f__elist->cierr,112,"bad repetition count");
			}
		poststar = havestar = 1;
		*sp = 0;
		f__lcount = atoi(s);
		goto retry;
		}
	if (ch == '.') {
#ifndef ALLOW_FLOAT_IN_INTEGER_LIST_INPUT
		if (reqint)
			errfl(f__elist->cierr,115,"invalid integer");
#endif
		GETC(ch);
		if (sp == sp1)
			while(ch == '0') {
				++havenum;
				--exp;
				GETC(ch);
				}
		while(isdigit(ch)) {
			if (sp < spe)
				{ *sp++ = ch; --exp; }
			GETC(ch);
			}
		}
	havenum += sp - sp1;
	se = 0;
	if (issign(ch))
		goto signonly;
	if (havenum && isexp(ch)) {
#ifndef ALLOW_FLOAT_IN_INTEGER_LIST_INPUT
		if (reqint)
			errfl(f__elist->cierr,115,"invalid integer");
#endif
		GETC(ch);
		if (issign(ch)) {
signonly:
			if (ch == '-') se = 1;
			GETC(ch);
			}
		if (!isdigit(ch)) {
bad:
			errfl(f__elist->cierr,112,"exponent field");
			}

		e = ch - '0';
		while(isdigit(GETC(ch))) {
			e = 10*e + ch - '0';
			if (e > EXPMAX)
				goto bad;
			}
		if (se)
			exp -= e;
		else
			exp += e;
		}
	(void) Ungetc(ch, f__cf);
	if (sp > sp1) {
		++havenum;
		while(*--sp == '0')
			++exp;
		if (exp)
			sprintf(sp+1, "e%ld", exp);
		else
			sp[1] = 0;
		f__lx = atof(s);
#ifdef Allow_TYQUAD
		if (reqint&2 && (se = sp - sp1 + exp) > 14 && se < 20) {
			/* Assuming 64-bit longint and 32-bit long. */
			if (exp < 0)
				sp += exp;
			if (sp1 <= sp) {
				f__llx = *sp1 - '0';
				while(++sp1 <= sp)
					f__llx = 10*f__llx + (*sp1 - '0');
				}
			while(--exp >= 0)
				f__llx *= 10;
			if (*s == '-')
				f__llx = -f__llx;
			}
#endif
		}
	else
		f__lx = 0.;
	if (havenum)
		f__ltype = TYLONG;
	else
		switch(ch) {
			case ',':
			case '/':
				break;
			default:
				if (havestar && ( ch == ' '
						||ch == '\t'
						||ch == '\n'))
					break;
				if (nml_read > 1) {
					f__lquit = 2;
					return 0;
					}
				errfl(f__elist->cierr,112,"invalid number");
			}
	return 0;
	}