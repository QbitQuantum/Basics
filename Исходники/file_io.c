int open_outfile()         /* return 1 if fail */
{
#ifdef DOS_NT_OS2
    if (stat(filename, &statbuf) == 0 && !(statbuf.st_mode & S_IWRITE))
        chmod(filename, S_IREAD | S_IWRITE);
#endif
#ifdef UNIX
    if (stat(filename, &statbuf) == 0 && unlink(filename) < 0) {
        FPRINTF(stderr, LoadFarString(CannotDeleteOldFile), filename);
        return 1;
    }
#endif
#ifdef TOPS20
    char *tfilnam;

    if ((tfilnam = (char *)malloc(2*strlen(filename)+1)) == (char *)NULL)
        return 1;
    strcpy(tfilnam, filename);
    upper(tfilnam);
    enquote(tfilnam);
    if ((outfile = fopen(tfilnam, FOPW)) == (FILE *)NULL) {
        FPRINTF(stderr, LoadFarString(CannotCreateFile), tfilnam);
        free(tfilnam);
        return 1;
    }
    free(tfilnam);
#else
#ifdef MTS
    if (aflag)
        outfile = fopen(filename, FOPWT);
    else
        outfile = fopen(filename, FOPW);
    if (outfile == (FILE *)NULL) {
        FPRINTF(stderr, LoadFarString(CannotCreateFile), filename);
        return 1;
    }
#else
    if ((outfile = fopen(filename, FOPW)) == (FILE *)NULL) {
        FPRINTF(stderr, LoadFarString(CannotCreateFile), filename);
        return 1;
    }
#endif
#endif

#if 0      /* this SUCKS!  on Ultrix, it must be writing a byte at a time... */
    setbuf(outfile, (char *)NULL);   /* make output unbuffered */
#endif

#ifdef USE_FWRITE
#ifdef DOS_NT_OS2
    /* 16-bit MSC: buffer size must be strictly LESS than 32K (WSIZE):  bogus */
    setbuf(outfile, (char *)NULL);   /* make output unbuffered */
#else /* !DOS_NT_OS2 */
#ifdef _IOFBF  /* make output fully buffered (works just about like write()) */
    setvbuf(outfile, (char *)slide, _IOFBF, WSIZE);
#else
    setbuf(outfile, (char *)slide);
#endif
#endif /* ?DOS_NT_OS2 */
#endif /* USE_FWRITE */
    return 0;

} /* end function open_outfile() */