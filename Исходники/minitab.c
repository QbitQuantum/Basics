SEXP
read_mtp(SEXP fname)
{
    FILE *f;
    char buf[MTP_BUF_SIZE], blank[1], *pres;
    MTB  *mtb, thisRec;
    int i, j, res, nMTB = MTB_INITIAL_ENTRIES;

    PROTECT(fname = asChar(fname));
#ifdef WIN32 /* force text-mode read */
    if ((f = fopen(R_ExpandFileName(CHAR(fname)), "rt")) == NULL)
#else
    if ((f = fopen(R_ExpandFileName(CHAR(fname)), "r")) == NULL)
#endif
	error(_("unable to open file '%s': '%s'"), 
	      CHAR(fname), strerror(errno));
    if ((fgets(buf, MTP_BUF_SIZE, f) == NULL) ||
	strncmp(buf, "Minitab Portable Worksheet ", 27) != 0)
	error(_("file '%s' is not in Minitab Portable Worksheet format"),
	      CHAR(fname));
    pres = fgets(buf, MTP_BUF_SIZE, f);
    if(pres != buf) error(_("file read error"));
    UNPROTECT(1);

    mtb = Calloc(nMTB, MTB);
    for (i = 0; !feof(f); i++) {
	if (i >= nMTB) {
	    nMTB *= 2;
	    mtb = Realloc(mtb, nMTB, MTB);
	}
	thisRec = mtb[i] = Calloc(1, MTBDATC);
	if (sscanf(buf, "%%%7d%7d%7d%7d%c%8c", &(thisRec->type),
		   &(thisRec->cnum), &(thisRec->len),
		   &(thisRec->dtype), blank, thisRec->name) != 6)
	    error(_("first record for entry %d is corrupt"), i+1);
	thisRec->name[8] = '\0';
	strtrim(thisRec->name);	/* trim trailing white space on name */
	switch (thisRec->dtype) {
	case 0:		/* numeric data */
	    thisRec->dat.ndat = Calloc(thisRec->len, double);
	    for (j = 0; j < thisRec->len; j++) {
		res = fscanf(f, "%lg", thisRec->dat.ndat + j);
		if(res == EOF) error(_("file read error"));
	    }
	    break;
	default:
	    if (thisRec->type == 4) { /* we have a matrix so dtype is number of columns */
		thisRec->dat.ndat = Calloc(thisRec->len, double);
		for (j = 0; j < thisRec->len; j++) {
		    res = fscanf(f, "%lg", thisRec->dat.ndat + j);
		    if(res == EOF) error(_("file read error"));
		}
	    } else {
		error(_("non-numeric data types are not yet implemented"));
	    }
	}