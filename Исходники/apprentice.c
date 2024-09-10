/*
 * parse a file or directory of files
 * const char *fn: name of magic file or directory
 */
static int apprentice_load(RMagic *ms, struct r_magic **magicp, ut32 *nmagicp, const char *fn, int action) {
	ut32 marraycount, i, mentrycount = 0, starttest;
	struct r_magic_entry *marray;
	char subfn[MAXPATHLEN];
	struct dirent *d;
	struct stat st;
	int errs = 0;
	DIR *dir;

	ms->flags |= R_MAGIC_CHECK;	/* Enable checks for parsed files */

        maxmagic = MAXMAGIS;
	if ((marray = calloc (maxmagic, sizeof(*marray))) == NULL) {
		file_oomem (ms, maxmagic * sizeof(*marray));
		return -1;
	}
	marraycount = 0;

	/* print silly verbose header for USG compat. */
	if (action == FILE_CHECK)
		eprintf ("%s\n", usg_hdr);

	/* load directory or file */
	if (stat (fn, &st) == 0 && S_ISDIR (st.st_mode)) {
		if (r_sandbox_enable (0) && !r_sandbox_check_path (fn)) {
			free (marray);
			return  -1;
		}
		dir = opendir (fn);
		if (dir) {
			while ((d = readdir (dir))) {
				if (*d->d_name=='.') continue;
				snprintf (subfn, sizeof (subfn), "%s/%s", fn, d->d_name);
				if (stat (subfn, &st) == 0 && S_ISREG (st.st_mode))
					load_1 (ms, action, subfn, &errs, &marray, &marraycount);
				//else perror (subfn);
			}
			closedir (dir);
		} else errs++;
	} else load_1 (ms, action, fn, &errs, &marray, &marraycount);
	if (errs)
		goto out;

	/* Set types of tests */
	for (i = 0; i < marraycount; ) {
		if (marray[i].mp->cont_level != 0) {
			i++;
			continue;
		}

		starttest = i;
		do {
			set_test_type(marray[starttest].mp, marray[i].mp);
			if (ms->flags & R_MAGIC_DEBUG) {
				(void)fprintf(stderr, "%s%s%s: %s\n",
					marray[i].mp->mimetype,
					marray[i].mp->mimetype[0] == '\0' ? "" : "; ",
					marray[i].mp->desc[0] ? marray[i].mp->desc : "(no description)",
					marray[i].mp->flag & BINTEST ? "binary" : "text");
				if (marray[i].mp->flag & BINTEST) {
#define SYMBOL "text"
#define SYMLEN sizeof(SYMBOL)
					char *p = strstr(marray[i].mp->desc, "text");
					if (p && (p == marray[i].mp->desc || isspace((unsigned char)p[-1])) &&
					    (p + SYMLEN - marray[i].mp->desc == MAXstring ||
					     (p[SYMLEN] == '\0' || isspace((unsigned char)p[SYMLEN])))) {
						(void)fprintf(stderr,
							      "*** Possible binary test for text type\n");
					}
#undef SYMBOL
#undef SYMLEN
				}
			}
		} while (++i < marraycount && marray[i].mp->cont_level != 0);
	}

	qsort (marray, marraycount, sizeof(*marray), apprentice_sort);

	/*
	 * Make sure that any level 0 "default" line is last (if one exists).
	 */
	for (i = 0; i < marraycount; i++) {
		if (marray[i].mp->cont_level == 0 &&
		    marray[i].mp->type == FILE_DEFAULT) {
			while (++i < marraycount)
				if (marray[i].mp->cont_level == 0)
					break;
			if (i != marraycount) {
				ms->line = marray[i].mp->lineno; /* XXX - Ugh! */
				file_magwarn (ms, "level 0 \"default\" did not sort last");
			}
			break;
		}
	}

	for (i = 0; i < marraycount; i++)
		mentrycount += marray[i].cont_count;

	if ((*magicp = malloc (1+(sizeof(**magicp) * mentrycount))) == NULL) {
		file_oomem (ms, sizeof(**magicp) * mentrycount);
		errs++;
		goto out;
	}

	mentrycount = 0;
	for (i = 0; i < marraycount; i++) {
		(void)memcpy (*magicp + mentrycount, marray[i].mp,
		    marray[i].cont_count * sizeof (**magicp));
		mentrycount += marray[i].cont_count;
	}
out:
	for (i = 0; i < marraycount; i++)
		free(marray[i].mp);
	free (marray);
	if (errs) {
		*magicp = NULL;
		*nmagicp = 0;
		return errs;
	}
	*nmagicp = mentrycount;
	return 0;
}