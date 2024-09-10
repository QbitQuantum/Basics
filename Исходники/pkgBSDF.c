/* Load a BSDF XML file and produce a corresponding Radiance object */
static int
cvtBSDF(char *fname)
{
	int	retOK;
	SDData	myBSDF;
	char	*pname, *fnbeg;
					/* find and load the XML file */
	retOK = strlen(fname);
	if (retOK < 5 || strcmp(fname+retOK-4, ".xml")) {
		fprintf(stderr, "%s: input does not end in '.xml'\n", fname);
		return(0);
	}
	pname = getpath(fname, getrlibpath(), R_OK);
	if (pname == NULL) {
		fprintf(stderr, "%s: cannot find BSDF file\n", fname);
		return(0);
	}
	fnbeg = strrchr(fname, DIRSEP);
	if (fnbeg != NULL)		/* eliminate directory */
		fname = fnbeg+1;
	SDclearBSDF(&myBSDF, fname);
	if (SDreportError(SDloadFile(&myBSDF, pname), stderr))
		return(0);
	retOK = (myBSDF.dim[0] > FTINY) & (myBSDF.dim[1] > FTINY);
	if (!retOK) {
		fprintf(stderr, "%s: zero width or height\n", fname);
	} else {
		if (!do_stdout) {
			char	rname[SDnameLn+4];
			strcpy(rname, myBSDF.name);
			strcat(rname, ".rad");
			retOK = (freopen(rname, "w", stdout) != NULL);
		}
		if (retOK) {
			if (myBSDF.matn[0] && myBSDF.makr[0])
				printf("# Material '%s' by '%s'\n\n",
						myBSDF.matn, myBSDF.makr);
			if (myBSDF.mgf == NULL) {
				faceBSDF(&myBSDF, .0);
			} else {
				faceBSDF(&myBSDF, myBSDF.dim[2]);
				if (myBSDF.rb != NULL)
					faceBSDF(&myBSDF, -myBSDF.dim[2]);
				retOK = geomBSDF(&myBSDF);
			}
		}
	}
	SDfreeBSDF(&myBSDF);		/* clean up and return */
	return(retOK);
}