/*
 * ar_close()
 *	closes archive device, increments volume number, and prints i/o summary
 */
void
ar_close(void)
{
	int status;

	if (arfd < 0) {
		did_io = io_ok = flcnt = 0;
		return;
	}

	/*
	 * Close archive file. This may take a LONG while on tapes (we may be
	 * forced to wait for the rewind to complete) so tell the user what is
	 * going on (this avoids the user hitting control-c thinking pax is
	 * broken).
	 */
	if (vflag && (artyp == ISTAPE)) {
		if (vfpart)
			(void)putc('\n', listf);
		(void)fprintf(listf,
			"%s: Waiting for tape drive close to complete...",
			argv0);
		(void)fflush(listf);
	}

	/*
	 * if nothing was written to the archive (and we created it), we remove
	 * it
	 */
	if (can_unlnk && (fstat(arfd, &arsb) == 0) && (S_ISREG(arsb.st_mode)) &&
	    (arsb.st_size == 0)) {
		(void)unlink(arcname);
		can_unlnk = 0;
	}

	/*
	 * for a quick extract/list, pax frequently exits before the child
	 * process is done
	 */
	if ((act == LIST || act == EXTRACT) && nflag && zpid > 0)
		kill(zpid, SIGINT);

	(void)close(arfd);

	/* Do not exit before child to ensure data integrity */
	if (zpid > 0)
		waitpid(zpid, &status, 0);

	if (vflag && (artyp == ISTAPE)) {
		(void)fputs("done.\n", listf);
		vfpart = 0;
		(void)fflush(listf);
	}
	arfd = -1;

	if (!io_ok && !did_io) {
		flcnt = 0;
		return;
	}
	did_io = io_ok = 0;

	/*
	 * The volume number is only increased when the last device has data
	 * and we have already determined the archive format.
	 */
	if (frmt != NULL)
		++arvol;

	if (!vflag) {
		flcnt = 0;
		return;
	}

	/*
	 * Print out a summary of I/O for this archive volume.
	 */
	if (vfpart) {
		(void)putc('\n', listf);
		vfpart = 0;
	}

	/*
	 * If we have not determined the format yet, we just say how many bytes
	 * we have skipped over looking for a header to id. there is no way we
	 * could have written anything yet.
	 */
	if (frmt == NULL) {
#	ifdef NET2_STAT
		(void)fprintf(listf, "%s: unknown format, %lu bytes skipped.\n",
		    argv0, rdcnt);
#	else
		(void)fprintf(listf, "%s: unknown format, %ju bytes skipped.\n",
		    argv0, (uintmax_t)rdcnt);
#	endif
		(void)fflush(listf);
		flcnt = 0;
		return;
	}

	if (strcmp(NM_CPIO, argv0) == 0)
		(void)fprintf(listf, "%llu blocks\n",
		    (unsigned long long)((rdcnt ? rdcnt : wrcnt) / 5120));
	else if (strcmp(NM_TAR, argv0) != 0)
		(void)fprintf(listf,
#	ifdef NET2_STAT
		    "%s: %s vol %d, %lu files, %lu bytes read, %lu bytes written.\n",
		    argv0, frmt->name, arvol-1, flcnt, rdcnt, wrcnt);
#	else
		    "%s: %s vol %d, %ju files, %ju bytes read, %ju bytes written.\n",
		    argv0, frmt->name, arvol-1, (uintmax_t)flcnt,
		    (uintmax_t)rdcnt, (uintmax_t)wrcnt);
#	endif
	(void)fflush(listf);
	flcnt = 0;
}