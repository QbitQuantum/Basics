/*
 * refclock_sample - process a pile of samples from the clock
 *
 * This routine implements a recursive median filter to suppress spikes
 * in the data, as well as determine a performance statistic. It
 * calculates the mean offset and RMS jitter. A time adjustment
 * fudgetime1 can be added to the final offset to compensate for various
 * systematic errors. The routine returns the number of samples
 * processed, which could be zero.
 */
static int
refclock_sample(
	struct refclockproc *pp		/* refclock structure pointer */
	)
{
	size_t	i, j, k, m, n;
	double	off[MAXSTAGE];
	double	offset;

	/*
	 * Copy the raw offsets and sort into ascending order. Don't do
	 * anything if the buffer is empty.
	 */
	n = 0;
	while (pp->codeproc != pp->coderecv) {
		pp->codeproc = (pp->codeproc + 1) % MAXSTAGE;
		off[n] = pp->filter[pp->codeproc];
		n++;
	}
	if (n == 0)
		return (0);

	if (n > 1)
		qsort((void *)off, n, sizeof(off[0]), refclock_cmpl_fp);

	/*
	 * Reject the furthest from the median of the samples until
	 * approximately 60 percent of the samples remain.
	 */
	i = 0; j = n;
	m = n - (n * 4) / 10;
	while ((j - i) > m) {
		offset = off[(j + i) / 2];
		if (off[j - 1] - offset < offset - off[i])
			i++;	/* reject low end */
		else
			j--;	/* reject high end */
	}

	/*
	 * Determine the offset and jitter.
	 */
	pp->offset = 0;
	pp->jitter = 0;
	for (k = i; k < j; k++) {
		pp->offset += off[k];
		if (k > i)
			pp->jitter += SQUARE(off[k] - off[k - 1]);
	}
	pp->offset /= m;
	pp->jitter = max(SQRT(pp->jitter / m), LOGTOD(sys_precision));
#ifdef DEBUG
	if (debug)
		printf(
		    "refclock_sample: n %d offset %.6f disp %.6f jitter %.6f\n",
		    n, pp->offset, pp->disp, pp->jitter);
#endif
	return (int)n;
}