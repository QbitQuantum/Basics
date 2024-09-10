int getfileline(void *vp, char *linebuf, int linebuf_size)
{
	/* Static buffers we will return. */
	FILE *fp = (FILE *)vp;
	unsigned char   c;
	unsigned char  *p;
	size_t linebuf_len;

	if (fp == NULL) {
		DEBUG(0,("getfileline: Bad file pointer.\n"));
		return -1;
	}

	/*
	 * Scan the file, a line at a time.
	 */
	while (!feof(fp)) {
		linebuf[0] = '\0';

		fgets(linebuf, linebuf_size, fp);
		if (ferror(fp)) {
			return -1;
		}

		/*
		 * Check if the string is terminated with a newline - if not
		 * then we must keep reading and discard until we get one.
		 */

		linebuf_len = strlen(linebuf);
		if (linebuf_len == 0) {
			linebuf[0] = '\0';
			return 0;
		}

		if (linebuf[linebuf_len - 1] != '\n') {
			c = '\0';
			while (!ferror(fp) && !feof(fp)) {
				c = fgetc(fp);
				if (c == '\n') {
					break;
				}
			}
		} else {
			linebuf[linebuf_len - 1] = '\0';
		}

#ifdef DEBUG_PASSWORD
		DEBUG(100, ("getfileline: got line |%s|\n", linebuf));
#endif
		if ((linebuf[0] == 0) && feof(fp)) {
			DEBUG(4, ("getfileline: end of file reached\n"));
			return 0;
		}

		if (linebuf[0] == '#' || linebuf[0] == '\0') {
			DEBUG(6, ("getfileline: skipping comment or blank line\n"));
			continue;
		}

		p = (unsigned char *) strchr_m(linebuf, ':');
		if (p == NULL) {
			DEBUG(0, ("getfileline: malformed line entry (no :)\n"));
			continue;
		}
		return linebuf_len;
	}
	return -1;
}