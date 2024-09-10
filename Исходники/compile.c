static int make_ofile(int kflag, char **Cflags, char *o_file, char *c_file)
{
#if	!defined(USE_WIN32)
    int		pid;
#endif

    struct stat	stat_c, stat_o;

    static char	*cnp	= (char *)NULL;
    char	*av[64];		/* hope that this is enough! */
    int		status;
    int		ac, i;

/*  FIRSTLY, ENSURE THAT THE SOURCEFILE EXISTS AND NEEDS RECOMPILING */

    if(stat(c_file, &stat_c) == -1) {
       fprintf(stderr,"%s: cannot find sourcefile %s\n",argv0,c_file);
	++nerrors;
	return(-1);
    }
    if(stat(o_file, &stat_o) == 0 && stat_c.st_mtime <= stat_o.st_mtime)
	return(0);

#if	CHECK_RECEIVE_SPELLING
    if(spell_check(c_file) == FALSE)
	return(-1);
#endif

    if(cnp == (char *)NULL) {
	cnp	= find_cnetfile("cnet.h", TRUE, TRUE);
	if(vflag)
	    fprintf(stderr,"using include directory \"%s\"\n", cnp);
    }

#if defined(USE_WIN32)
    ac	= 0;

    av[ac++] = "CL";
    av[ac++] = OS_DEFINE;

    av[ac++] =	"/DHAVE_LONG_LONG=1";
    sprintf(chararray, "/DSIZEOF_INT=%d",	sizeof(int));
    av[ac++] =	strdup(chararray);
    sprintf(chararray, "/DSIZEOF_LONG=%d",	sizeof(long));
    av[ac++] =	strdup(chararray);

    sprintf(chararray, "/I%s", cnp);
    av[ac++] = strdup(chararray);

    while(*Cflags)		/* add C compiler switches */
	av[ac++] =	*Cflags++;

    av[ac++] = "/c";
    sprintf(chararray, "/Fo%s", o_file);
    av[ac++] = strdup(chararray);

    if(!vflag)
	av[ac++] = "/NOLOGO";

    av[ac++] = c_file;
    av[ac  ] =	NULL;

    if(dflag) {
	fputs(av[0], stderr);
	for(i=1 ; i<ac ; i++)
	    fprintf(stderr," %s",av[i]);
	fputc('\n',stderr);
    }
    else
	fprintf(stderr,"compiling %s\n", c_file);

    status  = _spawnvp(_P_WAIT, av[0], &av[1]);
    if(status != 0) {
	if(status == -1)
	    fprintf(stderr,"%s: spawn of %s unsuccessful: %s\n",
				argv0,av[0],_sys_errlist[(int)errno]);
	exit(1);
    }

#else
    switch (pid = fork()) {
    case -1 :
	fprintf(stderr,"%s: cannot fork\n",argv0);
	exit(1);
	break;
    case 0 :
	ac	 = 0;

#if	USE_GCC_COMPILER
	av[ac++] = findenv("CNETGCC", CNETGCC);
	av[ac++] = "gcc";
	if(!kflag)			/* not using "old" K&R C */
	    av[ac++] = "-ansi";
#if	GCC_WERROR_WANTED
	av[ac++] = "-Werror";
#endif
#if	GCC_WALL_WANTED
	av[ac++] = "-Wall";
#endif

#else
	av[ac++] = findenv("CNETCC", CNETCC);
	av[ac++] = "cc";
#endif

	ac	 =	add_compile_args(ac, av, kflag);
	av[ac++] =	OS_DEFINE;

#if	HAVE_LONG_LONG
	av[ac++] =	"-DHAVE_LONG_LONG=1";
#endif
	sprintf(chararray, "-DSIZEOF_INT=%d",	sizeof(int));
	av[ac++] =	strdup(chararray);
	sprintf(chararray, "-DSIZEOF_LONG=%d",	sizeof(long));
	av[ac++] =	strdup(chararray);

	while(*Cflags)		/* add C compiler switches */
	    av[ac++] =	*Cflags++;

	sprintf(chararray, "-I%s", cnp);
	av[ac++] =	strdup(chararray);

	av[ac++] =	"-c";
	av[ac++] =	"-o";
	av[ac++] =	o_file;
	av[ac++] =	c_file;
	av[ac  ] =	NULL;

	if(dflag) {
	    fputs(av[0], stderr);
	    for(i=2 ; i<ac ; i++)
		fprintf(stderr," %s",av[i]);
	    fputc('\n',stderr);
	}
	else
	    fprintf(stderr,"compiling %s\n", c_file);

	execvp(av[0], &av[1]);
	fprintf(stderr,"%s: cannot exec %s\n",argv0,av[0]);
	exit(1);
        break;

    default :
	while(wait(&status) != pid)
	    ;
	if(status != 0)
	    exit(1);
	break;
    }
#endif
    return(0);
}