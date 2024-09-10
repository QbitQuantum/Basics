int diag_tty_break(struct diag_l0_device *dl0d, const int ms)
{
	HANDLE hd;
	long h;

	/*
	 * I'm going through this convoluted two-step conversion
	 * to avoid compiler warnings:
	 */

	h = get_osfhandle(dl0d->fd);
	hd = (HANDLE)h;

	if (tcdrain(dl0d->fd)) {
			fprintf(stderr, FLFMT "tcdrain returned %s.\n",
				FL, strerror(errno));
			return diag_iseterr(DIAG_ERR_GENERAL);
		}

	SetCommBreak(hd);
	diag_os_millisleep(ms);
	ClearCommBreak(hd);

	return 0;
}