/* Get output stream pointer (open and write header if new and noopen==0) */
STREAMOUT *
getostream(const char *ospec, const char *mname, int bn, int noopen)
{
	static STREAMOUT	stdos;
	char			info[1024];
	int			ofl;
	char			oname[1024];
	LUENT			*lep;
	STREAMOUT		*sop;
	char			*cp;
	
	if (ospec == NULL) {			/* use stdout? */
		if (!noopen & !using_stdout) {
			if (outfmt != 'a')
				SET_FILE_BINARY(stdout);
			if (header) {
				cp = info;
				if (yres > 0) {
					sprintf(cp, "NROWS=%d\n", yres *
							(xres + !xres) );
					while (*cp) ++cp;
				}
				if ((xres <= 0) | (stdos.reclen > 1))
					sprintf(cp, "NCOLS=%d\n", stdos.reclen);
				printheader(stdout, info);
			}
			if (stdos.reclen == 1)
				printresolu(stdout, xres, yres);
			if (waitflush > 0)
				fflush(stdout);
			stdos.xr = xres; stdos.yr = yres;
#ifdef getc_unlocked
			flockfile(stdout);	/* avoid lock/unlock overhead */
#endif
			using_stdout = 1;
		}
		stdos.ofp = stdout;
		stdos.reclen += noopen;
		return(&stdos);
	}
	ofl = ofname(oname, ospec, mname, bn);	/* get output name */
	if (ofl < 0) {
		sprintf(errmsg, "bad output format '%s'", ospec);
		error(USER, errmsg);
	}
	lep = lu_find(&ofiletab, oname);	/* look it up */
	if (lep->key == NULL)			/* new entry */
		lep->key = strcpy((char *)malloc(strlen(oname)+1), oname);
	sop = (STREAMOUT *)lep->data;
	if (sop == NULL) {			/* allocate stream */
		sop = (STREAMOUT *)malloc(sizeof(STREAMOUT));
		if (sop == NULL)
			error(SYSTEM, "out of memory in getostream");
		sop->outpipe = (oname[0] == '!');
		sop->reclen = 0;
		sop->ofp = NULL;		/* open iff noopen==0 */
		sop->xr = xres; sop->yr = yres;
		lep->data = (char *)sop;
		if (!sop->outpipe & !force_open & !recover &&
				access(oname, F_OK) == 0) {
			errno = EEXIST;		/* file exists */
			goto openerr;
		}
	} else if (noopen && outfmt == 'c' &&	/* stream exists to picture? */
			(sop->xr > 0) & (sop->yr > 0)) {
		if (ofl & OF_BIN)
			return(NULL);		/* let caller offset bins */
		sprintf(errmsg, "output '%s' not a valid picture", oname);
		error(WARNING, errmsg);
	}
	if (!noopen && sop->ofp == NULL) {	/* open output stream */
		if (oname[0] == '!')		/* output to command */
			sop->ofp = popen(oname+1, "w");
		else				/* else open file */
			sop->ofp = fopen(oname, "w");
		if (sop->ofp == NULL)
			goto openerr;
		if (outfmt != 'a')
			SET_FILE_BINARY(sop->ofp);
#ifdef getc_unlocked
		flockfile(sop->ofp);		/* avoid lock/unlock overhead */
#endif
		if (accumulate > 0) {		/* global resolution */
			sop->xr = xres; sop->yr = yres;
		}
		if (header) {
			cp = info;
			if (ofl & OF_MODIFIER || sop->reclen == 1) {
				sprintf(cp, "MODIFIER=%s\n", mname);
				while (*cp) ++cp;
			}
			if (ofl & OF_BIN) {
				sprintf(cp, "BIN=%d\n", bn);
				while (*cp) ++cp;
			}
			if (sop->yr > 0) {
				sprintf(cp, "NROWS=%d\n", sop->yr *
						(sop->xr + !sop->xr) );
				while (*cp) ++cp;
			}
			if ((sop->xr <= 0) | (sop->reclen > 1))
				sprintf(cp, "NCOLS=%d\n", sop->reclen);
			printheader(sop->ofp, info);
		}
		if (sop->reclen == 1)
			printresolu(sop->ofp, sop->xr, sop->yr);
		if (waitflush > 0)
			fflush(sop->ofp);
	}
	sop->reclen += noopen;			/* add to length if noopen */
	return(sop);				/* return output stream */
openerr:
	sprintf(errmsg, "cannot open '%s' for writing", oname);
	error(SYSTEM, errmsg);
	return(NULL);	/* pro forma return */
}