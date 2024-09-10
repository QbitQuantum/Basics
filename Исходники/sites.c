int G_oldsite_describe(FILE * ptr, int *dims, int *cat, int *strs, int *dbls)

/*-
 * Tries to guess the format of a sites list (the dimensionality,
 * the presence/type of a category, and the number of string and decimal
 * attributes) by reading the first record in the file.
 * Reads ptr and returns 0 on success,
 *                      -1 on EOF,
 *                      -2 for other error.
 */
{
    char sbuf[MAX_SITE_LEN], *buf;
    char ebuf[128], nbuf[128];
    int err;
    int itmp;
    float ftmp;

    if (G_ftell(ptr) != 0L) {
	fprintf(stderr,
		"\nPROGRAMMER ERROR: G_oldsite_describe() must be called\n");
	fprintf(stderr, "        immediately after G_fopen_sites_old()\n");
	return -2;
    }

    *dims = *strs = *dbls = 0;
    *cat = -1;
    buf = sbuf;

    if ((buf = fgets(sbuf, 1024, ptr)) == (char *)NULL) {
	rewind(ptr);
	return EOF;
    }
    /* skip over comment & header lines */
    while ((*buf == '#' || !isdigit(*buf)) && *buf != '-' && *buf != '+')
	if ((buf = fgets(sbuf, 1024, ptr)) == (char *)NULL) {
	    rewind(ptr);
	    return EOF;
	}

    if (buf[strlen(buf) - 1] == '\n')
	buf[strlen(buf) - 1] = '\0';

    if ((err = sscanf(buf, "%[^|]|%[^|]|%*[^\n]", ebuf, nbuf)) < 2) {
	fprintf(stderr, "ERROR: ebuf %s nbuf %s\n", ebuf, nbuf);
	rewind(ptr);
	return -2;
    }
    *dims = 2;

    /* move pointer past easting and northing fields */
    while (!ispipe(*buf) && !isnull(*buf))
	buf++;
    if (!isnull(*buf) && !isnull(*(buf + 1)))
	buf++;
    else {
	rewind(ptr);
	return -2;
    }
    while (!ispipe(*buf) && !isnull(*buf))
	buf++;
    if (!isnull(*buf) && !isnull(*(buf + 1)))
	buf++;
    else {
	rewind(ptr);
	return 0;
    }

    /* check for remaining dimensional fields */
    while (strchr(buf, PIPE) != (char *)NULL) {
	(*dims)++;
	while (!ispipe(*buf) && !isnull(*buf))
	    buf++;
	if (isnull(*buf) || isnull(*(buf + 1))) {
	    rewind(ptr);
	    return 0;
	}
	if (!isnull(*(buf + 1)))
	    buf++;
	else {
	    rewind(ptr);
	    return -2;
	}
    }

    /* no more dimensions-now we parse attribute fields */
    while (!isnull(*buf)) {
	switch (*buf) {
	case '#':		/* category field */
	    sscanf(buf, "#%s ", ebuf);
	    if (strstr(ebuf, ".") == NULL && sscanf(ebuf, "%d", &itmp) == 1)
		*cat = CELL_TYPE;
	    else if (strstr(ebuf, ".") != NULL &&
		     sscanf(ebuf, "%f", &ftmp) == 1)
		*cat = FCELL_TYPE;
	    else
		*cat = -1;

	    /* move to beginning of next attribute */
	    while (!isspace(*buf) && !isnull(*buf))
		buf++;
	    if (isnull(*buf) || isnull(*(buf + 1))) {
		rewind(ptr);
		return 0;
	    }
	    else
		buf++;
	    break;
	case '%':		/* decimal attribute */
	    (*dbls)++;
	    /* move to beginning of next attribute */
	    while (!isspace(*buf) && !isnull(*buf))
		buf++;
	    if (isnull(*buf) || isnull(*(buf + 1))) {
		rewind(ptr);
		return 0;
	    }
	    else
		buf++;
	    break;
	case '@':		/* string attribute */
	    if (isnull(*buf) || isnull(*(buf + 1))) {
		rewind(ptr);
		return 0;
	    }
	    else
		buf++;
	default:		/* defaults to string attribute */
	    /* allow both prefixed and unprefixed strings */
	    if ((err = cleanse_string(buf)) > 0) {
		(*strs)++;
		buf += err;
	    }

	    /* move to beginning of next attribute */
	    while (!isspace(*buf) && !isnull(*buf))
		buf++;
	    if (isnull(*buf) || isnull(*(buf + 1))) {
		rewind(ptr);
		return 0;
	    }
	    else
		buf++;
	    break;
	}
    }

    rewind(ptr);
    return 0;
}