static void dig_holes(int fd, off_t off, off_t len)
{
	off_t end = len ? off + len : 0;
	off_t hole_start = 0, hole_sz = 0;
	uintmax_t ct = 0;
	size_t  bufsz;
	char *buf;
	struct stat st;
#if defined(POSIX_FADV_SEQUENTIAL) && defined(HAVE_POSIX_FADVISE)
	off_t cache_start = off;
	/*
	 * We don't want to call POSIX_FADV_DONTNEED to discard cached
	 * data in PAGE_SIZE steps. IMHO it's overkill (too many syscalls).
	 *
	 * Let's assume that 1MiB (on system with 4K page size) is just
	 * a good compromise.
	 *					    -- kzak Feb-2014
	 */
	const size_t cachesz = getpagesize() * 256;
#endif

	if (fstat(fd, &st) != 0)
		err(EXIT_FAILURE, _("stat of %s failed"), filename);

	bufsz = st.st_blksize;

	if (lseek(fd, off, SEEK_SET) < 0)
		err(EXIT_FAILURE, _("seek on %s failed"), filename);

	/* buffer + extra space for is_nul() sentinel */
	buf = xmalloc(bufsz + sizeof(uintptr_t));
#if defined(POSIX_FADV_SEQUENTIAL) && defined(HAVE_POSIX_FADVISE)
	posix_fadvise(fd, off, 0, POSIX_FADV_SEQUENTIAL);
#endif

	while (end == 0 || off < end) {
		ssize_t rsz;

		rsz = pread(fd, buf, bufsz, off);
		if (rsz < 0 && errno)
			err(EXIT_FAILURE, _("%s: read failed"), filename);
		if (end && rsz > 0 && off > end - rsz)
			rsz = end - off;
		if (rsz <= 0)
			break;

		if (is_nul(buf, rsz)) {
			if (!hole_sz) {				/* new hole detected */
				int rc = skip_hole(fd, &off);
				if (rc == 0)
					continue;	/* hole skipped */
				else if (rc == 1)
					break;		/* end of file */
				hole_start = off;
			}
			hole_sz += rsz;
		 } else if (hole_sz) {
			xfallocate(fd, FALLOC_FL_PUNCH_HOLE|FALLOC_FL_KEEP_SIZE,
				   hole_start, hole_sz);
			ct += hole_sz;
			hole_sz = hole_start = 0;
		}

#if defined(POSIX_FADV_DONTNEED) && defined(HAVE_POSIX_FADVISE)
		/* discard cached data */
		if (off - cache_start > (off_t) cachesz) {
			size_t clen = off - cache_start;

			clen = (clen / cachesz) * cachesz;
			posix_fadvise(fd, cache_start, clen, POSIX_FADV_DONTNEED);
			cache_start = cache_start + clen;
		}
#endif
		off += rsz;
	}

	if (hole_sz) {
		xfallocate(fd, FALLOC_FL_PUNCH_HOLE|FALLOC_FL_KEEP_SIZE,
				hole_start, hole_sz);
		ct += hole_sz;
	}

	free(buf);

	if (verbose) {
		char *str = size_to_human_string(SIZE_SUFFIX_3LETTER | SIZE_SUFFIX_SPACE, ct);
		fprintf(stdout, _("%s: %s (%ju bytes) converted to sparse holes.\n"),
				filename, str, ct);
		free(str);
	}
}