int
FTPRemoteGlob(FTPCIPtr cip, FTPLineListPtr fileList, const char *pattern, int doGlob)
{
    char *cp;
    const char *lsflags;
    FTPLinePtr lp;
    int result;

    if (cip == NULL)
        return (kErrBadParameter);
    if (strcmp(cip->magic, kLibraryMagic))
        return (kErrBadMagic);

    if (fileList == NULL)
        return (kErrBadParameter);
    InitLineList(fileList);

    if ((pattern == NULL) || (pattern[0] == '\0'))
        return (kErrBadParameter);

    /* Note that we do attempt to use glob characters even if the remote
     * host isn't UNIX.  Most non-UNIX remote FTP servers look for UNIX
     * style wildcards.
     */
    if ((doGlob == 1) && (GLOBCHARSINSTR(pattern)))
    {
        /* Use NLST, which lists files one per line. */
        lsflags = "";

        /* Optimize for "NLST *" case which is same as "NLST". */
        if (strcmp(pattern, "*") == 0)
        {
            pattern = "";
            lsflags = (cip->hasNLST_a == kCommandNotAvailable) ? "" : "-a";
        }
        else if (strcmp(pattern, "**") == 0)
        {
            /* Hack; Lets you try "NLST -a" if you're daring. */
            /* Need to use "NLST -a" whenever possible,
             * because wu-ftpd doesn't do NLST right, IMHO.
             * (It doesn't include directories in the NLST
             *  if you do "NLST /the/dir" without -a.)
             */
            pattern = "";
            lsflags = (cip->hasNLST_a == kCommandNotAvailable) ? "" : "-a";
        }

        if ((result = FTPListToMemory2(cip, pattern, fileList, lsflags, 0, (int *) 0)) < 0)
        {
            if (*lsflags == '\0')
                return (result);
            if (strchr(lsflags, 'a') != NULL)
            {
                /* Try again, without "-a" */
                cip->hasNLST_a = kCommandNotAvailable;
                lsflags = "";
                if ((result = FTPListToMemory2(cip, pattern, fileList, lsflags, 0, (int *) 0)) < 0)
                {
                    return (result);
                }
                /* else proceed */
            }
            else
            {
                return (result);
            }
        }
#if 0
        DisposeLineListContents(fileList);
        InitLineList(fileList);
        AddLine(fileList, "../FAKEME1.txt");
        AddLine(fileList, "../../FAKEME2.txt");
        AddLine(fileList, "..\\FAKEME3.txt");
        AddLine(fileList, "..\\..\\FAKEME4.txt");
        AddLine(fileList, "...\\FAKEME5.txt");
        AddLine(fileList, "/tmp/bad/FAKEME6.txt");
        AddLine(fileList, "c:\\temp\\FAKEME7.txt");
        AddLine(fileList, "foo/../FAKEME8.txt");
        AddLine(fileList, "foo\\bar\\...\\FAKEME9.txt");
#endif
        if (fileList->first == NULL)
        {
            cip->errNo = kErrGlobNoMatch;
            return (kErrGlobNoMatch);
        }
        if (fileList->first == fileList->last)
        {
#define glberr(a) (ISTRNEQ(cp, a, strlen(a)))
            /* If we have only one item in the list, see if it really was
             * an error message we would recognize.
             */
            cp = strchr(fileList->first->line, ':');
            if (cp != NULL)
            {
                if (glberr(": No such file or directory"))
                {
                    (void) RemoveLine(fileList, fileList->first);
                    cip->errNo = kErrGlobFailed;
                    return (kErrGlobFailed);
                }
                else if (glberr(": No match"))
                {
                    cip->errNo = kErrGlobNoMatch;
                    return (kErrGlobNoMatch);
                }
            }
        }
        StripUnneccesaryGlobEntries(cip, fileList);
        RemoteGlobCollapse(cip, pattern, fileList);
        for (lp=fileList->first; lp != NULL; lp = lp->next)
            PrintF(cip, "  Rglob [%s]\n", lp->line);
    }
    else
    {
        /* Or, if there were no globbing characters in 'pattern', then the
         * pattern is really just a filename.  So for this case the
         * file list is really just a single file.
         */
        fileList->first = fileList->last = NULL;
        (void) AddLine(fileList, pattern);
    }
    return (kNoErr);
}	/* FTPRemoteGlob */