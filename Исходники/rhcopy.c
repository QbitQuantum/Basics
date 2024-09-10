int
openholo(		/* open existing holodeck file for i/o */
	char	*fname,
	int	append
)
{
	FILE	*fp;
	int	fd;
	int	hflags = 0;
	off_t	nextloc;
	int	n;
					/* open holodeck file */
	if ((fp = fopen(fname, append ? "r+" : "r")) == NULL) {
		sprintf(errmsg, "cannot open \"%s\" for %s", fname,
				append ? "appending" : "reading");
		error(SYSTEM, errmsg);
	}
					/* check header and magic number */
	if (getheader(fp, holheadline, &hflags) < 0 ||
			hflags&H_BADF || getw(fp) != HOLOMAGIC) {
		sprintf(errmsg, "file \"%s\" not in holodeck format", fname);
		error(USER, errmsg);
	}
	fd = dup(fileno(fp));			/* dup file handle */
	nextloc = ftell(fp);			/* get stdio position */
	fclose(fp);				/* done with stdio */
	for (n = 0; nextloc > 0L; n++) {	/* initialize each section */
		lseek(fd, nextloc, SEEK_SET);
		read(fd, (char *)&nextloc, sizeof(nextloc));
		hdinit(fd, NULL)->priv = hflags&H_OBST ? &obstr :
				hflags&H_OBSF ? &unobstr : (char *)NULL;
	}
	return(n);
}