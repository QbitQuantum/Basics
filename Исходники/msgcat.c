static nl_catd
loadCat(__const char *catpath)
{
	MCHeaderT       header;
	MCCatT          *cat;
	MCSetT          *set;
	int32_t         i;
	off_t           nextSet;
	int             saverr;
	int		fd;

	if ((cat = (MCCatT *)malloc(sizeof(MCCatT))) == NULL)
		return (NLERR);

	if ((fd = open(catpath, O_RDONLY | O_CLOEXEC)) == -1) {
		saverr = errno;
		free(cat);
		errno = saverr;
		return (NLERR);
	}

	if ((cat->fp = fdopen(fd, "r")) == NULL) {
		saverr = errno;
		close(fd);
		free(cat);
		errno = saverr;
		return (NLERR);
	}

	if (fread(&header, sizeof(header), 1, cat->fp) != 1 ||
	    strncmp(header.magic, MCMagic, MCMagicLen) != 0)
		CORRUPT();

	if (ntohl(header.majorVer) != MCMajorVer) {
		(void)fclose(cat->fp);
		free(cat);
		if (OSSwapInt32(ntohl(header.majorVer)) == MCMajorVer) {
		    (void)fprintf(stderr, "%s: %s is the wrong byte ordering.\n", _errowner, catpath);
		} else {
		    (void)fprintf(stderr, "%s: %s is version %d, we need %d.\n", _errowner, catpath, (int)ntohl(header.majorVer), MCMajorVer);
		}
		NLRETERR(EFTYPE);
	}
	if (ntohl(header.numSets) <= 0) {
		(void)fclose(cat->fp);
		free(cat);
		(void)fprintf(stderr, "%s: %s has %d sets!\n",
		    _errowner, catpath, (int)ntohl(header.numSets));
		NLRETERR(EFTYPE);
	}

	cat->numSets = ntohl(header.numSets);
	if ((cat->sets = (MCSetT *)malloc(sizeof(MCSetT) * cat->numSets)) ==
	    NULL)
		NOSPACE();

	nextSet = ntohll(header.firstSet);
	for (i = 0; i < cat->numSets; ++i) {
		if (fseeko(cat->fp, nextSet, SEEK_SET) == -1) {
			__nls_free_resources(cat, i);
			CORRUPT();
		}

		/* read in the set header */
		set = cat->sets + i;
		if (fread(set, sizeof(*set), 1, cat->fp) != 1) {
			__nls_free_resources(cat, i);
			CORRUPT();
		}

		/* if it's invalid, skip over it (and backup 'i') */
		if (set->invalid) {
			--i;
			nextSet = ntohll(set->nextSet);
			continue;
		}
		set->invalid = TRUE;
		nextSet = ntohll(set->nextSet);
	}

	return ((nl_catd) cat);
}