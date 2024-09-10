/*
 * Getent implements the functions of cgetent.  If fd is non-negative,
 * *db_array has already been opened and fd is the open file descriptor.  We
 * do this to save time and avoid using up file descriptors for tc=
 * recursions.
 *
 * Getent returns the same success/failure codes as cgetent.  On success, a
 * pointer to a malloc'ed capability record with all tc= capabilities fully
 * expanded and its length (not including trailing ASCII NUL) are left in
 * *cap and *len.
 *
 * Basic algorithm:
 *	+ Allocate memory incrementally as needed in chunks of size BFRAG
 *	  for capability buffer.
 *	+ Recurse for each tc=name and interpolate result.  Stop when all
 *	  names interpolated, a name can't be found, or depth exceeds
 *	  MAX_RECURSION.
 */
static int getent(char **cap, char **db_array, char *nfield, const char *name, size_t *len, int fd, int depth)
{
	DB *capdbp = NULL;
	char *r_end, *rp = NULL, **db_p;	/* pacify gcc */
	int myfd = 0, eof, foundit, retval;
	size_t clen;
	char *record, *cbuf, *newrecord;
	int tc_not_resolved;
	char pbuf[MAXPATHLEN];

	assert(cap != NULL);
	assert(len != NULL);
	assert(db_array != NULL);
	/* fd may be -1 */
	assert(name != NULL);
	/* nfield may be NULL */

	/*
	 * Return with ``loop detected'' error if we've recursed more than
	 * MAX_RECURSION times.
	 */
	if (depth > MAX_RECURSION)
		return (-3);

	/*
	 * Check if we have a top record from cgetset().
         */
	if (depth == 0 && toprec != NULL && cgetmatch(toprec, strdup(name)) == 0) {
		if ((record = malloc (topreclen + BFRAG)) == NULL) {
			errno = ENOMEM;
			return (-2);
		}
		(void)strcpy(record, toprec);	/* XXX: strcpy is safe */
		db_p = db_array;
		rp = record + topreclen + 1;
		r_end = rp + BFRAG;
		goto tc_exp;
	}
	/*
	 * Allocate first chunk of memory.
	 */
	if ((record = malloc(BFRAG)) == NULL) {
		errno = ENOMEM;
		return (-2);
	}
	r_end = record + BFRAG;
	foundit = 0;
	/*
	 * Loop through database array until finding the record.
	 */

	for (db_p = db_array; *db_p != NULL; db_p++) {
		eof = 0;

		/*
		 * Open database if not already open.
		 */

		if (fd >= 0) {
			(void)lseek(fd, (off_t)0, SEEK_SET);
		} else {
			(void)snprintf(pbuf, sizeof(pbuf), "%s.db", *db_p);
#if defined(__linux__)
			if ((capdbp->open(capdbp, NULL, pbuf, "", DB_HASH, DB_RDONLY, 0)) == 0) {
#else
			if ((capdbp = dbopen(pbuf, O_RDONLY, 0, DB_HASH, 0)) != NULL) {
#endif /* !__linux__ */
				free(record);
				retval = cdbget(capdbp, &record, name);
				if (retval < 0) {
					/* no record available */
					(void)capdbp->close(capdbp, 0);
					return (retval);
				}
				/* save the data; close frees it */
				clen = strlen(record);
				cbuf = malloc(clen + 1);
				memmove(cbuf, record, clen + 1);
				if (capdbp->close(capdbp, 0) < 0) {
					int serrno = errno;

					free(cbuf);
					errno = serrno;
					return (-2);
				}
				*len = clen;
				*cap = cbuf;
				return (retval);
			} else {
				fd = open(*db_p, O_RDONLY, 0);
				if (fd < 0) {
					/* No error on unfound file. */
					continue;
				}
				myfd = 1;
			}
		}
		/*
		 * Find the requested capability record ...
		 */
		{
		char buf[BUFSIZ];
		char *b_end, *bp, *cp;
		int c, slash;

		/*
		 * Loop invariants:
		 *	There is always room for one more character in record.
		 *	R_end always points just past end of record.
		 *	Rp always points just past last character in record.
		 *	B_end always points just past last character in buf.
		 *	Bp always points at next character in buf.
		 *	Cp remembers where the last colon was.
		 */
		b_end = buf;
		bp = buf;
		cp = 0;
		slash = 0;
		for (;;) {

			/*
			 * Read in a line implementing (\, newline)
			 * line continuation.
			 */
			rp = record;
			for (;;) {
				if (bp >= b_end) {
					int n;

					n = read(fd, buf, sizeof(buf));
					if (n <= 0) {
						if (myfd)
							(void)close(fd);
						if (n < 0) {
							int serrno = errno;

							free(record);
							errno = serrno;
							return (-2);
						} else {
							fd = -1;
							eof = 1;
							break;
						}
					}
					b_end = buf+n;
					bp = buf;
				}

				c = *bp++;
				if (c == '\n') {
					if (slash) {
						slash = 0;
						rp--;
						continue;
					} else
						break;
				}
				if (slash) {
					slash = 0;
					cp = 0;
				}
				if (c == ':') {
					/*
					 * If the field was `empty' (i.e.
					 * contained only white space), back up
					 * to the colon (eliminating the
					 * field).
					 */
					if (cp)
						rp = cp;
					else
						cp = rp;
				} else if (c == '\\') {
					slash = 1;
				} else if (c != ' ' && c != '\t') {
					/*
					 * Forget where the colon was, as this
					 * is not an empty field.
					 */
					cp = 0;
				}
				*rp++ = c;

				/*
				 * Enforce loop invariant: if no room 
				 * left in record buffer, try to get
				 * some more.
				 */
				if (rp >= r_end) {
					u_int pos;
					size_t newsize;

					pos = rp - record;
					newsize = r_end - record + BFRAG;
					newrecord = realloc(record, newsize);
					if (newrecord == NULL) {
						free(record);
						if (myfd)
							(void)close(fd);
						errno = ENOMEM;
						return (-2);
					}
					record = newrecord;
					r_end = record + newsize;
					rp = record + pos;
				}
			}
			/* Eliminate any white space after the last colon. */
			if (cp)
				rp = cp + 1;
			/* Loop invariant lets us do this. */
			*rp++ = '\0';

			/*
			 * If encountered eof check next file.
			 */
			if (eof)
				break;

			/*
			 * Toss blank lines and comments.
			 */
			if (*record == '\0' || *record == '#')
				continue;

			/*
			 * See if this is the record we want ...
			 */
			if (cgetmatch(record, strdup(name)) == 0) {
				if (nfield == NULL || !nfcmp(nfield, record)) {
					foundit = 1;
					break;	/* found it! */
				}
			}
		}
	}
		if (foundit)
			break;
	}

	if (!foundit)
		return (-1);

	/*
	 * Got the capability record, but now we have to expand all tc=name
	 * references in it ...
	 */
tc_exp:	{
		char *newicap, *s;
		size_t ilen, newilen;
		int diff, iret, tclen;
		char *icap, *scan, *tc, *tcstart, *tcend;

		/*
		 * Loop invariants:
		 *	There is room for one more character in record.
		 *	R_end points just past end of record.
		 *	Rp points just past last character in record.
		 *	Scan points at remainder of record that needs to be
		 *	scanned for tc=name constructs.
		 */
		scan = record;
		tc_not_resolved = 0;
		for (;;) {
			if ((tc = cgetcap(scan, "tc", '=')) == NULL)
				break;

			/*
			 * Find end of tc=name and stomp on the trailing `:'
			 * (if present) so we can use it to call ourselves.
			 */
			s = tc;
			for (;;)
				if (*s == '\0')
					break;
				else
					if (*s++ == ':') {
						*(s - 1) = '\0';
						break;
					}
			tcstart = tc - 3;
			tclen = s - tcstart;
			tcend = s;

			iret = getent(&icap, (char **)&ilen, (char *)db_p, (const char *)&fd, (size_t *)tc, depth+1, 0);
			newicap = icap;		/* Put into a register. */
			newilen = ilen;
			if (iret != 0) {
				/* an error */
				if (iret < -1) {
					if (myfd)
						(void)close(fd);
					free(record);
					return (iret);
				}
				if (iret == 1)
					tc_not_resolved = 1;
				/* couldn't resolve tc */
				if (iret == -1) {
					*(s - 1) = ':';
					scan = s - 1;
					tc_not_resolved = 1;
					continue;
				}
			}
			/* not interested in name field of tc'ed record */
			s = newicap;
			for (;;)
				if (*s == '\0')
					break;
				else
					if (*s++ == ':')
						break;
			newilen -= s - newicap;
			newicap = s;

			/* make sure interpolated record is `:'-terminated */
			s += newilen;
			if (*(s-1) != ':') {
				*s = ':';	/* overwrite NUL with : */
				newilen++;
			}

			/*
			 * Make sure there's enough room to insert the
			 * new record.
			 */
			diff = newilen - tclen;
			if (diff >= r_end - rp) {
				u_int pos, tcpos, tcposend;
				size_t newsize;

				pos = rp - record;
				newsize = r_end - record + diff + BFRAG;
				tcpos = tcstart - record;
				tcposend = tcend - record;
				newrecord = realloc(record, newsize);
				if (newrecord == NULL) {
					free(record);
					if (myfd)
						(void)close(fd);
					free(icap);
					errno = ENOMEM;
					return (-2);
				}
				record = newrecord;
				r_end = record + newsize;
				rp = record + pos;
				tcstart = record + tcpos;
				tcend = record + tcposend;
			}

			/*
			 * Insert tc'ed record into our record.
			 */
			s = tcstart + newilen;
			memmove(s, tcend,  (size_t)(rp - tcend));
			memmove(tcstart, newicap, newilen);
			rp += diff;
			free(icap);

			/*
			 * Start scan on `:' so next cgetcap works properly
			 * (cgetcap always skips first field).
			 */
			scan = s-1;
		}
	}
	/*
	 * Close file (if we opened it), give back any extra memory, and
	 * return capability, length and success.
	 */
	if (myfd)
		(void)close(fd);
	*len = rp - record - 1;	/* don't count NUL */
	if (r_end > rp) {
		if ((newrecord = realloc(record, (size_t)(rp - record))) == NULL) {
			free(record);
			errno = ENOMEM;
			return (-2);
		}
		record = newrecord;
	}

	*cap = record;
	if (tc_not_resolved)
		return (1);
	return (0);
}

/*
 * Cgetent extracts the capability record name from the NULL terminated file
 * array db_array and returns a pointer to a malloc'd copy of it in buf.
 * Buf must be retained through all subsequent calls to cgetcap, cgetnum,
 * cgetflag, and cgetstr, but may then be free'd.  0 is returned on success,
 * -1 if the requested record couldn't be found, -2 if a system error was
 * encountered (couldn't open/read a file, etc.), and -3 if a potential
 * reference loop is detected.
 */
int cgetent(char **buf, char **db_array, const char *name)
{
	size_t dummy;

	assert(buf != NULL);
	assert(db_array != NULL);
	assert(name != NULL);

	return (getent(buf, (char **)&dummy, (char *)db_array, (const char *)-1, (size_t *)name, 0, 0));
}