void PS_MakeGraph(CSOUND *csound, WINDAT *wdptr, const char *name)
{
    winEPS_globals_t  *pp;
    char      *filenam;
    char      pathnam[1024];
    char      *t;
    time_t    lt;
    OPARMS oparms;
     csound->GetOParms(csound, &oparms);
     IGN(wdptr);
     IGN(name);

    if (csound->winEPS_globals != NULL)
      return;
    csound->winEPS_globals = csound->Calloc(csound, sizeof(winEPS_globals_t));
    pp = (winEPS_globals_t *) csound->winEPS_globals;

    filenam = oparms.outfilename;
    if (filenam == NULL)
      filenam = "test";     /* O.outfilename not set yet */

    /*  If sound output is being piped directly to the DAC, then */
    /*  there is no PS output, (psFileOK remains 0),             */
    /*  otherwise open an encapsulated PostScript output file    */
    /*  with a name related to the sound file's name.            */
    /*                                                           */
    /*  The PS file is located in the same directory as the      */
    /*  sound file, and has the name of the sound file with the  */
    /*  extension ``.eps'' appended.                             */
    /*                                                           */

    /**
     *  Remove extension from sound-file and add ".eps"
     */
    strNcpy(pathnam, filenam, 1024); //pathnam[1023] = '\0';
    t = strrchr(pathnam, '.');
    if (t != NULL) *t = '\0';
    strlcat(pathnam, ".eps", 1024);
    pp->psfd = csound->FileOpen2(csound, &(pp->psFile), CSFILE_STD, pathnam,
                                   "w", "SFDIR", CSFTYPE_POSTSCRIPT, 0);
    if (UNLIKELY(pp->psfd == NULL)) {
      csound->Message(csound, Str("** Warning **  PostScript file %s "
                                  "cannot be opened\n"), pathnam);
      csound->winEPS_globals = NULL;
      csound->Free(csound, (void *)pp);
      return;
    }
    csound->Message(csound, Str("\n PostScript graphs written to file %s\n\n"),
                            pathnam);
    /**
     *  Get the current time and date
     */
    lt = time(NULL);
#ifndef LINUX
    {
      struct tm *date_ptr;
      char      *date;
      date_ptr = localtime(&lt);
      date = asctime(date_ptr);
      t = pp->ps_date;
      while (*date != '\n')
        *t++ = *date++;
      *t = '\0';
    }
#else
    /* avoid use of non-reentrant functions */
    {
      struct tm tmp1;
      memset(&tmp1, 0, sizeof(struct tm));
      localtime_r(&lt, &tmp1);
      asctime_r(&tmp1, &(pp->ps_date[0]));
    }
#endif
    /**
     *  Print PostScript file Header
     *  Place every plot on a new page.
     */
    fprintf(pp->psFile, "%s \n", "%!PS-Adobe-2.0");
    fprintf(pp->psFile, "%s \n", "%%Creator: Csound");
    fprintf(pp->psFile, "%s %s \n", "%%CreationDate:", pp->ps_date);
    fprintf(pp->psFile, "%s \n", "%%Pages: (atend)");
    fprintf(pp->psFile, "%s \n", "%%PageOrder: Ascend");
    fprintf(pp->psFile, "%s \n", "%%BoundingBox: 010 010 540 700");
    fprintf(pp->psFile, "%s \n", "%%Orientation: Portrait");
    fprintf(pp->psFile, "%s \n", "%%EndComments");
    fprintf(pp->psFile, "%s \n", "   ");
}