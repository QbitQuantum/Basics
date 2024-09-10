static void
setDolp(Char *cp)
{
    Char *dp;
    int i;

    if (dolnmod == 0 || dolmcnt == 0) {
	dolp = cp;
	return;
    }
    dp = cp = Strsave(cp);
    for (i = 0; i < dolnmod; i++) {
	/* handle s// [eichin:19910926.0510EST] */
	if(dolmod[i] == 's') {
	    int delim;
	    Char *lhsub, *rhsub, *np;
	    size_t lhlen = 0, rhlen = 0;
	    int didmod = 0;

	    delim = dolmod[++i];
	    if (!delim || letter(delim)
		|| Isdigit(delim) || any(" \t\n", delim)) {
		seterror(ERR_BADSUBST);
		break;
	    }
	    lhsub = &dolmod[++i];
	    while(dolmod[i] != delim && dolmod[++i]) {
		lhlen++;
	    }
	    dolmod[i] = 0;
	    rhsub = &dolmod[++i];
	    while(dolmod[i] != delim && dolmod[++i]) {
		rhlen++;
	    }
	    dolmod[i] = 0;

	    do {
		dp = Strstr(cp, lhsub);
		if (dp) {
		    size_t len = Strlen(cp) + 1 - lhlen + rhlen;

		    np = xreallocarray(NULL, len, sizeof(Char));
		    *dp = 0;
		    (void) Strlcpy(np, cp, len);
		    (void) Strlcat(np, rhsub, len);
		    (void) Strlcat(np, dp + lhlen, len);

		    xfree(cp);
		    dp = cp = np;
		    didmod = 1;
		} else {
		    /* should this do a seterror? */
		    break;
		}
	    }
	    while (dolwcnt == 10000);
	    /*
	     * restore dolmod for additional words
	     */
	    dolmod[i] = rhsub[-1] = delim;
	    if (didmod)
		dolmcnt--;
	    else
		break;
	} else {
	    int didmod = 0;

	    do {
		if ((dp = domod(cp, dolmod[i]))) {
		    didmod = 1;
		    if (Strcmp(cp, dp) == 0) {
			xfree(cp);
			cp = dp;
			break;
		    }
		    else {
			xfree(cp);
			cp = dp;
		    }
		}
		else
		    break;
	    }
	    while (dolwcnt == 10000);
	    dp = cp;
	    if (didmod)
		dolmcnt--;
	    else
		break;
	}
    }

    if (dp) {
	addla(dp);
	xfree(dp);
    }
    else
	addla(cp);

    dolp = STRNULL;
    if (seterr)
	stderror(ERR_OLD);
}