void
putprelude(void)
{	char snap[256]; FILE *fd;

	sprintf(snap, "%s.ps", oFname?oFname->name:"msc");
	if (!(pfd = fopen(snap, MFLAGS)))
		fatal("cannot create file '%s'", snap);

	fprintf(pfd, "%%!PS-Adobe-2.0\n");
	fprintf(pfd, "%%%%Creator: %s\n", SpinVersion);
	fprintf(pfd, "%%%%Title: MSC %s\n", oFname?oFname->name:"--");
	fprintf(pfd, "%%%%BoundingBox: 119 154 494 638\n");
	ntimes(pfd, 0, 1, PsPre);

	if (s_trail)
	{	if (ntrail)
		sprintf(snap, "%s%d.trail", oFname?oFname->name:"msc", ntrail);
		else
		sprintf(snap, "%s.trail", oFname?oFname->name:"msc");
		if (!(fd = fopen(snap, "r")))
		{	snap[strlen(snap)-2] = '\0';
			if (!(fd = fopen(snap, "r")))
				fatal("cannot open trail file", (char *) 0);
		}
		TotSteps = 1;
		while (fgets(snap, 256, fd)) TotSteps++;
		fclose(fd);
	}
	TotSteps += 10;
	R = (int   *) emalloc(TotSteps * sizeof(int));
	D = (int   *) emalloc(TotSteps * sizeof(int));
	M = (short *) emalloc(TotSteps * sizeof(short));
	T = (short *) emalloc(TotSteps * sizeof(short));
	L = (char **) emalloc(TotSteps * sizeof(char *));
	I = (char **) emalloc(TotSteps * sizeof(char *));
	ProcLine = (char *) emalloc(1024 * sizeof(char));
	startpage();
}