void
writepict(				/* write the picture to a file */
	char  *s
)
{
	static char  buf[128];
	char  *fname;
	FILE  *fp;
	COLR  *scanline;
	int  y;
				/* XXX relies on words.c 2.11 behavior */
	if (nextword(buf, sizeof(buf), s) == NULL && !buf[0]) {
		error(COMMAND, "no file");
		return;
	}
	if ((fname = getpath(buf, NULL, 0)) == NULL ||
			(fp = fopen(fname, "w")) == NULL) {
		sprintf(errmsg, "cannot open \"%s\"", buf);
		error(COMMAND, errmsg);
		return;
	}
	SET_FILE_BINARY(fp);
	(*dev->comout)("writing \"");
	(*dev->comout)(fname);
	(*dev->comout)("\"...\n");
						/* write header */
	newheader("RADIANCE", fp);
	fputs(progname, fp);
	fprintview(&ourview, fp);
	if (octname != NULL)
		fprintf(fp, " %s\n", octname);
	else
		putc('\n', fp);
	fprintf(fp, "SOFTWARE= %s\n", VersionID);
	fputnow(fp);
	if (exposure != 1.0)
		fputexpos(exposure, fp);
	if (dev->pixaspect != 1.0)
		fputaspect(dev->pixaspect, fp);
	fputformat(COLRFMT, fp);
	putc('\n', fp);
	fprtresolu(hresolu, vresolu, fp);

	scanline = (COLR *)malloc(hresolu*sizeof(COLR));
	if (scanline == NULL) {
		error(COMMAND, "not enough memory!");
		fclose(fp);
		unlink(fname);
		return;
	}
	for (y = vresolu-1; y >= 0; y--) {
		getpictcolrs(y, scanline, &ptrunk, hresolu, vresolu);
		if (fwritecolrs(scanline, hresolu, fp) < 0)
			break;
	}
	free((void *)scanline);
	if (fclose(fp) < 0)
		error(COMMAND, "write error");
}