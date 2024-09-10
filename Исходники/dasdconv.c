/*-------------------------------------------------------------------*/
static void
convert_ckd (int lfs, IFD ifd, char *ifname, int itrklen,
            BYTE *itrkbuf, int repl, int quiet,
            char *ofname, U16 devtype, U32 heads,
            U32 maxdlen, U32 volcyls, BYTE *volser)
{
int             i;                      /* Array subscript           */
char            *s;                     /* String pointer            */
int             fileseq;                /* File sequence number      */
char            sfname[260];            /* Suffixed name of this file*/
char            *suffix;                /* -> Suffix character       */
U32             endcyl;                 /* Last cylinder of this file*/
U32             cyl;                    /* Cylinder number           */
U32             cylsize;                /* Cylinder size in bytes    */
BYTE           *obuf;                   /* -> Output track buffer    */
U32             mincyls;                /* Minimum cylinder count    */
U32             maxcyls;                /* Maximum cylinder count    */
U32             maxcpif;                /* Maximum number of cylinders
                                           in each CKD image file    */
int             rec0len = 8;            /* Length of R0 data         */
U32             trksize;                /* AWSCKD image track length */

    /* Compute the AWSCKD image track length */
    trksize = sizeof(CKDDASD_TRKHDR)
                + sizeof(CKDDASD_RECHDR) + rec0len
                + sizeof(CKDDASD_RECHDR) + maxdlen
                + sizeof(eighthexFF);
    trksize = ROUND_UP(trksize,512);

    /* Compute minimum and maximum number of cylinders */
    cylsize = trksize * heads;
    mincyls = 1;

    if (!lfs)
    {
        maxcpif = 0x80000000 / cylsize;
        maxcyls = maxcpif * CKD_MAXFILES;
    }
    else
        maxcpif = maxcyls = volcyls;

    if (maxcyls > 65536) maxcyls = 65536;

    /* Check for valid number of cylinders */
    if (volcyls < mincyls || volcyls > maxcyls)
    {
        fprintf (stderr, MSG(HHC02421, "E",
                volcyls, mincyls, maxcyls));
        EXIT(4);
    }

    /* Obtain track data buffer */
    obuf = malloc(trksize);
    if (obuf == NULL)
    {
        char buf[40];
        MSGBUF( buf, "malloc(%u)", trksize);
        fprintf (stderr, MSG(HHC02412, "E", buf, strerror(errno)));
        EXIT(6);
    }

    /* Display progress message */
    fprintf (stderr, MSG(HHC02422, "I",
            devtype, volser, volcyls, heads, trksize));
#ifdef EXTERNALGUI
    if (extgui)
        fprintf (stderr, "CYLS=%u\n", volcyls);
#endif /*EXTERNALGUI*/

    /* Copy the unsuffixed AWSCKD image file name */
    strcpy (sfname, ofname);
    suffix = NULL;

    /* Create the suffixed file name if volume will exceed 2GB */
    if (volcyls > maxcpif)
    {
        /* Look for last slash marking end of directory name */
        s = strrchr (ofname, '/');
        if (s == NULL) s = ofname;

        /* Insert suffix before first dot in file name, or
           append suffix to file name if there is no dot */
        s = strchr (s, '.');
        if (s != NULL)
        {
            i = s - ofname;
            strcpy (sfname + i, "_1");
            strcat (sfname, ofname + i);
            suffix = sfname + i + 1;
        }
        else
        {
            strcat (sfname, "_1");
            suffix = sfname + strlen(sfname) - 1;
        }
    }

    /* Create the AWSCKD image files */
    for (cyl = 0, fileseq = 1; cyl < volcyls;
            cyl += maxcpif, fileseq++)
    {
        /* Insert the file sequence number in the file name */
        if (suffix) *suffix = '0' + fileseq;

        /* Calculate the ending cylinder for this file */
        if (cyl + maxcpif < volcyls)
            endcyl = cyl + maxcpif - 1;
        else
            endcyl = volcyls - 1;

        /* Create an AWSCKD image file */
        convert_ckd_file (ifd, ifname, itrklen, itrkbuf, repl, quiet,
                        sfname, fileseq, devtype, heads, trksize,
                        obuf, cyl, endcyl, volcyls, volser);
    }

    /* Release the output track buffer */
    free (obuf);

} /* end function convert_ckd */