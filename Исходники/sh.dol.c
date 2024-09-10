/*
 * Handle the multitudinous $ expansion forms.
 * Ugh.
 */
static void
Dgetdol(void)
{
    Char *np;
    struct varent *vp = NULL;
    struct Strbuf *name = Strbuf_alloc();
    eChar   c, sc;
    int     subscr = 0, lwb = 1, upb = 0;
    int    dimen = 0, bitset = 0, length = 0;
    static Char *dolbang = NULL;

    cleanup_push(name, Strbuf_free);
    dolmod.len = dolmcnt = dol_flag_a = 0;
    c = sc = DgetC(0);
    if (c == DEOF) {
      stderror(ERR_SYNTAX);
      return;
    }
    if (c == '{')
	c = DgetC(0);		/* sc is { to take } later */
    if ((c & TRIM) == '#')
	dimen++, c = DgetC(0);	/* $# takes dimension */
    else if (c == '?')
	bitset++, c = DgetC(0);	/* $? tests existence */
    else if (c == '%')
	length++, c = DgetC(0); /* $% returns length in chars */
    switch (c) {

    case '!':
	if (dimen || bitset || length)
	    stderror(ERR_SYNTAX);
	if (backpid != 0) {
	    xfree(dolbang);
	    setDolp(dolbang = putn(backpid));
	}
	cleanup_until(name);
	goto eatbrac;

    case '$':
	if (dimen || bitset || length)
	    stderror(ERR_SYNTAX);
	setDolp(doldol);
	cleanup_until(name);
	goto eatbrac;

    case '<'|QUOTE: {
	static struct Strbuf wbuf; /* = Strbuf_INIT; */

	if (bitset)
	    stderror(ERR_NOTALLOWED, "$?<");
	if (dimen)
	    stderror(ERR_NOTALLOWED, "$#<");
	if (length)
	    stderror(ERR_NOTALLOWED, "$%<");
	wbuf.len = 0;
	{
	    char cbuf[MB_LEN_MAX];
	    size_t cbp = 0;
	    int old_pintr_disabled;

	    for (;;) {
	        int len;
		ssize_t res;
		Char wc;

		pintr_push_enable(&old_pintr_disabled);
		res = force_read(OLDSTD, cbuf + cbp, 1);
		cleanup_until(&old_pintr_disabled);
		if (res != 1)
		    break;
		cbp++;
		len = normal_mbtowc(&wc, cbuf, cbp);
		if (len == -1) {
		    reset_mbtowc();
		    if (cbp < MB_LEN_MAX)
		        continue; /* Maybe a partial character */
		    wc = (unsigned char)*cbuf | INVALID_BYTE;
		}
		if (len <= 0)
		    len = 1;
		if (cbp != (size_t)len)
		    memmove(cbuf, cbuf + len, cbp - len);
		cbp -= len;
		if (wc == '\n')
		    break;
		Strbuf_append1(&wbuf, wc);
	    }
	    while (cbp != 0) {
		int len;
		Char wc;

		len = normal_mbtowc(&wc, cbuf, cbp);
		if (len == -1) {
		    reset_mbtowc();
		    wc = (unsigned char)*cbuf | INVALID_BYTE;
		}
		if (len <= 0)
		    len = 1;
		if (cbp != (size_t)len)
		    memmove(cbuf, cbuf + len, cbp - len);
		cbp -= len;
		if (wc == '\n')
		    break;
		Strbuf_append1(&wbuf, wc);
	    }
	    Strbuf_terminate(&wbuf);
	}

	fixDolMod();
	setDolp(wbuf.s); /* Kept allocated until next $< expansion */
	cleanup_until(name);
	goto eatbrac;
    }

    case '*':
	Strbuf_append(name, STRargv);
	Strbuf_terminate(name);
	vp = adrof(STRargv);
	subscr = -1;		/* Prevent eating [...] */
	break;

    case DEOF:
    case '\n':
	np = dimen ? STRargv : (bitset ? STRstatus : NULL);
	if (np) {
	    bitset = 0;
	    Strbuf_append(name, np);
	    Strbuf_terminate(name);
	    vp = adrof(np);
	    subscr = -1;		/* Prevent eating [...] */
	    unDredc(c);
	    break;
	}
	else
	    stderror(ERR_SYNTAX);
	/*NOTREACHED*/

    default:
	if (Isdigit(c)) {
	    if (dimen)
		stderror(ERR_NOTALLOWED, "$#<num>");
	    subscr = 0;
	    do {
		subscr = subscr * 10 + c - '0';
		c = DgetC(0);
	    } while (c != DEOF && Isdigit(c));
	    unDredc(c);
	    if (subscr < 0)
		stderror(ERR_RANGE);
	    if (subscr == 0) {
		if (bitset) {
		    dolp = dolzero ? STR1 : STR0;
		    cleanup_until(name);
		    goto eatbrac;
		}
		if (ffile == 0)
		    stderror(ERR_DOLZERO);
		if (length) {
		    length = Strlen(ffile);
		    addla(putn(length));
		}
		else {
		    fixDolMod();
		    setDolp(ffile);
		}
		cleanup_until(name);
		goto eatbrac;
	    }
#if 0
	    if (bitset)
		stderror(ERR_NOTALLOWED, "$?<num>");
	    if (length)
		stderror(ERR_NOTALLOWED, "$%<num>");
#endif
	    vp = adrof(STRargv);
	    if (vp == 0) {
		vp = &nulargv;
		cleanup_until(name);
		goto eatmod;
	    }
	    break;
	}
	if (c == DEOF || !alnum(c)) {
	    np = dimen ? STRargv : (bitset ? STRstatus : NULL);
	    if (np) {
		bitset = 0;
		Strbuf_append(name, np);
		Strbuf_terminate(name);
		vp = adrof(np);
		subscr = -1;		/* Prevent eating [...] */
		unDredc(c);
		break;
	    }
	    else
		stderror(ERR_VARALNUM);
	}
	for (;;) {
	    Strbuf_append1(name, (Char) c);
	    c = DgetC(0);
	    if (c == DEOF || !alnum(c))
		break;
	}
	Strbuf_terminate(name);
	unDredc(c);
	vp = adrof(name->s);
    }
    if (bitset) {
	dolp = (vp || getenv(short2str(name->s))) ? STR1 : STR0;
	cleanup_until(name);
	goto eatbrac;
    }
    if (vp == NULL || vp->vec == NULL) {
	np = str2short(getenv(short2str(name->s)));
	if (np) {
	    static Char *env_val; /* = NULL; */

	    cleanup_until(name);
	    fixDolMod();
	    if (length) {
		    addla(putn(Strlen(np)));
	    } else {
		    xfree(env_val);
		    env_val = Strsave(np);
		    setDolp(env_val);
	    }
	    goto eatbrac;
	}
	udvar(name->s);
	/* NOTREACHED */
    }
    cleanup_until(name);
    c = DgetC(0);
    upb = blklen(vp->vec);
    if (dimen == 0 && subscr == 0 && c == '[') {
	name = Strbuf_alloc();
	cleanup_push(name, Strbuf_free);
	np = name->s;
	for (;;) {
	    c = DgetC(DODOL);	/* Allow $ expand within [ ] */
	    if (c == ']')
		break;
	    if (c == '\n' || c == DEOF)
		stderror(ERR_INCBR);
	    Strbuf_append1(name, (Char) c);
	}
	Strbuf_terminate(name);
	np = name->s;
	if (dolp || dolcnt)	/* $ exp must end before ] */
	    stderror(ERR_EXPORD);
	if (!*np)
	    stderror(ERR_SYNTAX);
	if (Isdigit(*np)) {
	    int     i;

	    for (i = 0; Isdigit(*np); i = i * 10 + *np++ - '0')
		continue;
	    if (i < 0 || (i > upb && !any("-*", *np))) {
		cleanup_until(name);
		dolerror(vp->v_name);
		return;
	    }
	    lwb = i;
	    if (!*np)
		upb = lwb, np = STRstar;
	}
	if (*np == '*')
	    np++;
	else if (*np != '-')
	    stderror(ERR_MISSING, '-');
	else {
	    int i = upb;

	    np++;
	    if (Isdigit(*np)) {
		i = 0;
		while (Isdigit(*np))
		    i = i * 10 + *np++ - '0';
		if (i < 0 || i > upb) {
		    cleanup_until(name);
		    dolerror(vp->v_name);
		    return;
		}
	    }
	    if (i < lwb)
		upb = lwb - 1;
	    else
		upb = i;
	}
	if (lwb == 0) {
	    if (upb != 0) {
		cleanup_until(name);
		dolerror(vp->v_name);
		return;
	    }
	    upb = -1;
	}
	if (*np)
	    stderror(ERR_SYNTAX);
	cleanup_until(name);
    }
    else {
	if (subscr > 0) {
	    if (subscr > upb)
		lwb = 1, upb = 0;
	    else
		lwb = upb = subscr;
	}
	unDredc(c);
    }
    if (dimen) {
	/* this is a kludge. It prevents Dgetdol() from */
	/* pushing erroneous ${#<error> values into the labuf. */
	if (sc == '{') {
	    c = Dredc();
	    if (c != '}')
		stderror(ERR_MISSING, '}');
	    unDredc(c);
	}
	addla(putn(upb - lwb + 1));
    }
    else if (length) {
	int i;

	for (i = lwb - 1, length = 0; i < upb; i++)
	    length += Strlen(vp->vec[i]);
#ifdef notdef
	/* We don't want that, since we can always compute it by adding $#xxx */
	length += i - 1;	/* Add the number of spaces in */
#endif
	addla(putn(length));
    }
    else {
eatmod:
	fixDolMod();
	dolnxt = &vp->vec[lwb - 1];
	dolcnt = upb - lwb + 1;
    }
eatbrac:
    if (sc == '{') {
	c = Dredc();
	if (c != '}')
	    stderror(ERR_MISSING, '}');
    }
}