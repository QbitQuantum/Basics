/**
 * makehtml: make html files
 *
 *	@param[in]	total	number of files.
 */
static void
makehtml(int total)
{
	GFIND *gp;
	FILE *anchor_stream;
	const char *path;
	int count = 0;

	/*
	 * Create anchor stream for anchor_load().
	 */
	anchor_stream = tmpfile();
#if defined(_WIN32) && !defined(__CYGWIN__)
	/*
	 * tmpfile is created in the root, which user's can't write on Vista+.
	 * Use _tempnam and open it directly.
	 */
	if (anchor_stream == NULL) {
		char *name = _tempnam(tmpdir, "htags");
		anchor_stream = fopen(name, "w+bD");
		free(name);
	}
#endif
	gp = gfind_open(dbpath, NULL, other_files ? GPATH_BOTH : GPATH_SOURCE, 0);
	while ((path = gfind_read(gp)) != NULL) {
		if (gp->type == GPATH_OTHER)
			fputc(' ', anchor_stream);
		fputs(path, anchor_stream);
		fputc('\n', anchor_stream);
	}
	gfind_close(gp);
	/*
	 * Prepare anchor stream for anchor_load().
	 */
	anchor_prepare(anchor_stream);
	/*
	 * For each path in GPATH, convert the path into HTML file.
	 */
	gp = gfind_open(dbpath, NULL, other_files ? GPATH_BOTH : GPATH_SOURCE, 0);
	while ((path = gfind_read(gp)) != NULL) {
		char html[MAXPATHLEN];

		if (gp->type == GPATH_OTHER && !other_files)
			continue;
		/*
		 * load tags belonging to the path.
		 * The path must be start "./".
		 */
		anchor_load(path);
		/*
		 * inform the current path name to lex() function.
		 */
		save_current_path(path);
		count++;
		path += 2;		/* remove './' at the head */
		message(" [%d/%d] converting %s", count, total, path);
		snprintf(html, sizeof(html), "%s/%s/%s.%s", distpath, SRCS, path2fid(path), HTML);
		src2html(path, html, gp->type == GPATH_OTHER);
	}
	gfind_close(gp);
}