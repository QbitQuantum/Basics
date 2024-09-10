scandir(const char *dirname, struct dirent ***namelist,
    int (*select)(const struct dirent *), int (*dcomp)(const struct dirent **,
	const struct dirent **))
#endif
{
	struct dirent *d, *p, **names = NULL;
	size_t arraysz, numitems;
	DIR *dirp;

	if ((dirp = opendir(dirname)) == NULL)
		return(-1);

	numitems = 0;
	arraysz = 32;	/* initial estimate of the array size */
	names = (struct dirent **)malloc(arraysz * sizeof(struct dirent *));
	if (names == NULL)
		goto fail;

	while ((d = readdir(dirp)) != NULL) {
		if (select != NULL && !SELECT(d))
			continue;	/* just selected names */
		/*
		 * Make a minimum size copy of the data
		 */
		p = (struct dirent *)malloc(_GENERIC_DIRSIZ(d));
		if (p == NULL)
			goto fail;
		p->d_fileno = d->d_fileno;
		p->d_type = d->d_type;
		p->d_reclen = d->d_reclen;
		p->d_namlen = d->d_namlen;
		bcopy(d->d_name, p->d_name, p->d_namlen + 1);
		/*
		 * Check to make sure the array has space left and
		 * realloc the maximum size.
		 */
		if (numitems >= arraysz) {
			struct dirent **names2;

			names2 = reallocarray(names, arraysz,
			    2 * sizeof(struct dirent *));
			if (names2 == NULL) {
				free(p);
				goto fail;
			}
			names = names2;
			arraysz *= 2;
		}
		names[numitems++] = p;
	}
	closedir(dirp);
	if (numitems && dcomp != NULL)
#ifdef I_AM_SCANDIR_B
		qsort_b(names, numitems, sizeof(struct dirent *), (void*)dcomp);
#else
		qsort_r(names, numitems, sizeof(struct dirent *),
		    &dcomp, alphasort_thunk);
#endif
	*namelist = names;
	return (numitems);

fail:
	while (numitems > 0)
		free(names[--numitems]);
	free(names);
	closedir(dirp);
	return (-1);
}