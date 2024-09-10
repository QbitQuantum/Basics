/*
 * dcanon - canonicalize the pathname, removing excess ./ and ../ etc.
 *	we are of course assuming that the file system is standardly
 *	constructed (always have ..'s, directories have links)
 */
Char   *
dcanon(Char *cp, Char *p)
{
    Char *sp;
    Char *p1, *p2;	/* general purpose */
    int    slash;
#ifdef HAVE_SLASHSLASH
    int    slashslash;
#endif /* HAVE_SLASHSLASH */
    size_t  clen;

#ifdef S_IFLNK			/* if we have symlinks */
    Char *mlink, *newcp;
    char *tlink;
    size_t cc;
#endif /* S_IFLNK */

    clen = Strlen(cp);

    /*
     * christos: if the path given does not start with a slash prepend cwd. If
     * cwd does not start with a slash or the result would be too long try to
     * correct it.
     */
    if (!ABSOLUTEP(cp)) {
	Char *tmpdir;
	size_t	len;

	p1 = varval(STRcwd);
	if (p1 == STRNULL || !ABSOLUTEP(p1)) {
	    Char *new_cwd = agetcwd();

	    if (new_cwd == NULL) {
		xprintf("%s: %s\n", progname, strerror(errno));
		setcopy(STRcwd, str2short("/"), VAR_READWRITE|VAR_NOGLOB);
	    }
	    else
		setv(STRcwd, new_cwd, VAR_READWRITE|VAR_NOGLOB);
	    p1 = varval(STRcwd);
	}
	len = Strlen(p1);
	tmpdir = xmalloc((len + clen + 2) * sizeof (*tmpdir));
	(void) Strcpy(tmpdir, p1);
	(void) Strcat(tmpdir, STRslash);
	(void) Strcat(tmpdir, cp);
	xfree(cp);
	cp = p = tmpdir;
    }

#ifdef HAVE_SLASHSLASH
    slashslash = (cp[0] == '/' && cp[1] == '/');
#endif /* HAVE_SLASHSLASH */

    while (*p) {		/* for each component */
	sp = p;			/* save slash address */
	while (*++p == '/')	/* flush extra slashes */
	    continue;
	if (p != ++sp)
	    for (p1 = sp, p2 = p; (*p1++ = *p2++) != '\0';)
		continue;
	p = sp;			/* save start of component */
	slash = 0;
	if (*p) 
	    while (*++p)	/* find next slash or end of path */
		if (*p == '/') {
		    slash = 1;
		    *p = 0;
		    break;
		}

#ifdef HAVE_SLASHSLASH
	if (&cp[1] == sp && sp[0] == '.' && sp[1] == '.' && sp[2] == '\0')
	    slashslash = 1;
#endif /* HAVE_SLASHSLASH */
	if (*sp == '\0') {	/* if component is null */
	    if (--sp == cp)	/* if path is one char (i.e. /) */ 
		break;
	    else
		*sp = '\0';
	}
	else if (sp[0] == '.' && sp[1] == 0) {
	    if (slash) {
		for (p1 = sp, p2 = p + 1; (*p1++ = *p2++) != '\0';)
		    continue;
		p = --sp;
	    }
	    else if (--sp != cp)
		*sp = '\0';
	    else
		sp[1] = '\0';
	}
	else if (sp[0] == '.' && sp[1] == '.' && sp[2] == 0) {
	    /*
	     * We have something like "yyy/xxx/..", where "yyy" can be null or
	     * a path starting at /, and "xxx" is a single component. Before
	     * compressing "xxx/..", we want to expand "yyy/xxx", if it is a
	     * symbolic link.
	     */
	    *--sp = 0;		/* form the pathname for readlink */
#ifdef S_IFLNK			/* if we have symlinks */
	    if (sp != cp && /* symlinks != SYM_IGNORE && */
		(tlink = areadlink(short2str(cp))) != NULL) {
		mlink = str2short(tlink);
		xfree(tlink);

		if (slash)
		    *p = '/';
		/*
		 * Point p to the '/' in "/..", and restore the '/'.
		 */
		*(p = sp) = '/';
		if (*mlink != '/') {
		    /*
		     * Relative path, expand it between the "yyy/" and the
		     * "/..". First, back sp up to the character past "yyy/".
		     */
		    while (*--sp != '/')
			continue;
		    sp++;
		    *sp = 0;
		    /*
		     * New length is "yyy/" + mlink + "/.." and rest
		     */
		    p1 = newcp = xmalloc(((sp - cp) + Strlen(mlink) +
					  Strlen(p) + 1) * sizeof(Char));
		    /*
		     * Copy new path into newcp
		     */
		    for (p2 = cp; (*p1++ = *p2++) != '\0';)
			continue;
		    for (p1--, p2 = mlink; (*p1++ = *p2++) != '\0';)
			continue;
		    for (p1--, p2 = p; (*p1++ = *p2++) != '\0';)
			continue;
		    /*
		     * Restart canonicalization at expanded "/xxx".
		     */
		    p = sp - cp - 1 + newcp;
		}
		else {
		    newcp = Strspl(mlink, p);
		    /*
		     * Restart canonicalization at beginning
		     */
		    p = newcp;
		}
		xfree(cp);
		cp = newcp;
#ifdef HAVE_SLASHSLASH
                slashslash = (cp[0] == '/' && cp[1] == '/');
#endif /* HAVE_SLASHSLASH */
		continue;	/* canonicalize the link */
	    }
#endif /* S_IFLNK */
	    *sp = '/';
	    if (sp != cp)
		while (*--sp != '/')
		    continue;
	    if (slash) {
		for (p1 = sp + 1, p2 = p + 1; (*p1++ = *p2++) != '\0';)
		    continue;
		p = sp;
	    }
	    else if (cp == sp)
		*++sp = '\0';
	    else
		*sp = '\0';
	}
	else {			/* normal dir name (not . or .. or nothing) */

#ifdef S_IFLNK			/* if we have symlinks */
	    if (sp != cp && symlinks == SYM_CHASE &&
		(tlink = areadlink(short2str(cp))) != NULL) {
		mlink = str2short(tlink);
		xfree(tlink);

		/*
		 * restore the '/'.
		 */
		if (slash)
		    *p = '/';

		/*
		 * point sp to p (rather than backing up).
		 */
		sp = p;

		if (*mlink != '/') {
		    /*
		     * Relative path, expand it between the "yyy/" and the
		     * remainder. First, back sp up to the character past
		     * "yyy/".
		     */
		    while (*--sp != '/')
			continue;
		    sp++;
		    *sp = 0;
		    /*
		     * New length is "yyy/" + mlink + "/.." and rest
		     */
		    p1 = newcp = xmalloc(((sp - cp) + Strlen(mlink) +
					  Strlen(p) + 1) * sizeof(Char));
		    /*
		     * Copy new path into newcp
		     */
		    for (p2 = cp; (*p1++ = *p2++) != '\0';)
			continue;
		    for (p1--, p2 = mlink; (*p1++ = *p2++) != '\0';)
			continue;
		    for (p1--, p2 = p; (*p1++ = *p2++) != '\0';)
			continue;
		    /*
		     * Restart canonicalization at expanded "/xxx".
		     */
		    p = sp - cp - 1 + newcp;
		}
		else {
		    newcp = Strspl(mlink, p);
		    /*
		     * Restart canonicalization at beginning
		     */
		    p = newcp;
		}
		xfree(cp);
		cp = newcp;
#ifdef HAVE_SLASHSLASH
                slashslash = (cp[0] == '/' && cp[1] == '/');
#endif /* HAVE_SLASHSLASH */
		continue;	/* canonicalize the mlink */
	    }
#endif /* S_IFLNK */
	    if (slash)
		*p = '/';
	}
    }

    /*
     * fix home...
     */
#ifdef S_IFLNK
    p1 = varval(STRhome);
    cc = Strlen(p1);
    /*
     * See if we're not in a subdir of STRhome
     */
    if (p1 && *p1 == '/' && (Strncmp(p1, cp, cc) != 0 ||
	(cp[cc] != '/' && cp[cc] != '\0'))) {
	static ino_t home_ino = (ino_t) -1;
	static dev_t home_dev = (dev_t) -1;
	static Char *home_ptr = NULL;
	struct stat statbuf;
	int found;
	Char *copy;

	/*
	 * Get dev and ino of STRhome
	 */
	if (home_ptr != p1 &&
	    stat(short2str(p1), &statbuf) != -1) {
	    home_dev = statbuf.st_dev;
	    home_ino = statbuf.st_ino;
	    home_ptr = p1;
	}
	/*
	 * Start comparing dev & ino backwards
	 */
	p2 = copy = Strsave(cp);
	found = 0;
	while (*p2 && stat(short2str(p2), &statbuf) != -1) {
	    if (DEV_DEV_COMPARE(statbuf.st_dev, home_dev) &&
			statbuf.st_ino == home_ino) {
			found = 1;
			break;
	    }
	    if ((sp = Strrchr(p2, '/')) != NULL)
		*sp = '\0';
	}
	/*
	 * See if we found it
	 */
	if (*p2 && found) {
	    /*
	     * Use STRhome to make '~' work
	     */
	    newcp = Strspl(p1, cp + Strlen(p2));
	    xfree(cp);
	    cp = newcp;
	}
	xfree(copy);
    }
#endif /* S_IFLNK */

#ifdef HAVE_SLASHSLASH
    if (slashslash) {
	if (cp[1] != '/') {
	    p = xmalloc((Strlen(cp) + 2) * sizeof(Char));
	    *p = '/';
	    (void) Strcpy(&p[1], cp);
	    xfree(cp);
	    cp = p;
	}
    }
    if (cp[1] == '/' && cp[2] == '/') {
	for (p1 = &cp[1], p2 = &cp[2]; (*p1++ = *p2++) != '\0';)
	    continue;
    }
#endif /* HAVE_SLASHSLASH */
    return cp;
}