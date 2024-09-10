/*
 * Sets up the defragmentation of a file based on the 
 * filepath.  It collects the bstat information, does 
 * an open on the file and passes this all to fsrfile_common.
 */
static int
fsrfile(char *fname, xfs_ino_t ino)
{
	xfs_bstat_t	statbuf;
	jdm_fshandle_t	*fshandlep;
	int	fd, fsfd;
	int	error = 0;
	char	*tname;

	fshandlep = jdm_getfshandle(getparent (fname) );
	if (! fshandlep) {
		fsrprintf(
		  "unable to construct sys handle for %s: %s\n",
		  fname, strerror(errno));
		return -1;
	}

	/*
	 * Need to open something on the same filesystem as the
	 * file.  Open the parent.
	 */
	fsfd = open(getparent(fname), O_RDONLY);
	if (fsfd < 0) {
		fsrprintf(
		  "unable to open sys handle for %s: %s\n",
		  fname, strerror(errno));
		return -1;
	}
	
	if ((xfs_bulkstat_single(fsfd, &ino, &statbuf)) < 0) {
		fsrprintf(
		  "unable to get bstat on %s: %s\n",
		  fname, strerror(errno));
		close(fsfd);
		return -1;
	}
		
	fd = jdm_open( fshandlep, &statbuf, O_RDWR);
	if (fd < 0) {
		fsrprintf(
		  "unable to open handle %s: %s\n",
		  fname, strerror(errno));
		close(fsfd);
		return -1;
	}

	/* Get the fs geometry */
	if (xfs_getgeom(fsfd, &fsgeom) < 0 ) {
		fsrprintf("Unable to get geom on fs for: %s\n", fname);
		close(fsfd);
		return -1;
	}

	close(fsfd);

	tname = gettmpname(fname);

	if (tname)
		error = fsrfile_common(fname, tname, NULL, fd, &statbuf);

	close(fd);

	return error;
}