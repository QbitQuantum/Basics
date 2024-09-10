int
PicBuf_to_PAC (const GEN_PAR *pg, const OUT_PAR *po)
{

#define BLOCKS 100       /* max. 100 files        */

FILE    *fd;                    /* stream handle                */
int     x_screens, y_screens;   /* max. of file-counters        */
int     x, y;                   /* file-counters                */
char    basename[32];           /* filename without extension   */
char    filename[96];           /* filename, complete           */

static Byte screen[32000];      /* sorry for wasting memory,    */
				/* but there's no convincing    */
				/* STAD-packaging mechanism     */
				/* without at least 32000 bytes */
				/* of the valuable memory       */

Byte    packbyte;               /* most frequent byte in screen */
Byte    lablbyte;               /* indicates packbyte           */
Byte    specbyte;               /* indicates repetitions and    */
				/* pack-, labl- or specbyte     */

int     horicompr;              /* length horiz. compr. picture */
int     verticompr;             /* length verti. compr. picture */

const PicBuf *pb;

#ifdef VAX
int     hd;                     /* file handle                  */
#endif

  if (pg == NULL || po == NULL)
	return ERROR;
  pb = po->picbuf;
  if (pb == NULL)
	return ERROR;

  if (pb->depth > 1)
  {
	Eprintf ("\nPAC mode does not support colors yet -- sorry\n");
	return ERROR;
  }

 /**
  **  check number of screens (rows * columns)
  **/
  x_screens = (pb->nb - 1) / PAC_BPL;
  y_screens = (pb->nr - 1) / PAC_YRES;

  if (((x_screens + 1) * (y_screens + 1)) > BLOCKS)
  {
	PError("hp2xx -- Too many PAC files necessary");
	return ERROR;
  }

 /**
  **  action message
  **/
  if (!pg->quiet)
  {
      Eprintf ("\n\nWriting PAC output: %d rows of %d bytes\n",
		      pb->nr, pb->nb);
      Eprintf ("corresponding to %d x %d PAC-files\n",
		      x_screens + 1, y_screens + 1);
  }

 /**
  **  creat basename (filename without extension)
  **/
  if (*po->outfile != '-')
  {
	strncpy (basename, po->outfile, 6);
	basename[6] = '\0';
  }
  else
	strcpy  (basename, "stad");     /* Default name */

 /**
  **  run over all screens
  **/
  for (y = 0; y <= y_screens; y++)
  {
    for (x = 0; x <= x_screens; x++)
    {
	/* make actual filename */
	Name_PAC (filename, basename, y_screens, x, y);
	if (!pg->quiet)
	    Eprintf ("%s-> ", filename);

	/* collect data from hp2xx-bitmap   */
	if (!pg->quiet)
	    Eprintf ("data: fetch, ");
	Screen_for_PAC (pb, screen, x, y);

	/* determine pack-, label-, special-byte */
	if (!pg->quiet)
	    Eprintf ("analyse [1");
	Analyze_PAC(screen, &packbyte, &lablbyte, &specbyte);
	if (!pg->quiet)
	    Eprintf ("] ");

	/* preset file-descriptor (to give him a defined state) */
	fd = NULL;

	/* test horizontal compression mode */
	if (!pg->quiet)
	    Eprintf ("[2");
	if ((horicompr = Pack_PAC(screen, packbyte, lablbyte, specbyte,
			 TESTHORI, fd)) == ERROR)
	{
	    PError ("\nhp2xx -- test horiz.-PAC file");
	    return ERROR;
	}
	if (!pg->quiet)
	    Eprintf ("] ");

	/* test vertical compression mode */
	if (!pg->quiet)
	    Eprintf ("[3");
	if ((verticompr = Pack_PAC(screen, packbyte, lablbyte, specbyte,
			  TESTVERTI, fd)) == ERROR)
	{
	    PError ("\nhp2xx -- test vert.-PAC file");
	    return ERROR;
	}
	if (!pg->quiet)
	    Eprintf ("] ;");

	/* open file to write   */
	if (!pg->quiet)
	    Eprintf ("file: open, ");
#ifdef VAX
	if ((hd = creat(filename, 0,"rfm=var","mrs=512")) == -1)
	    PError ("\nhp2xx -- creating PAC-output file");
	if( (fd = fdopen(hd, WRITE_BIN)) == NULL)
	{
#else
	if ((fd = fopen(filename, WRITE_BIN)) == NULL)
	{
#endif
	    PError ("\nhp2xx -- opening PAC file");
	    return ERROR;
	}

	/* decide which file shall be written   */
	if (!pg->quiet)
	    Eprintf ("write, ");
	if (horicompr >= 32000 && verticompr >= 32000)
	{
	    /* no compression was sucessfull, write unpacked file   */
	    if (Pack_PAC(screen, packbyte, lablbyte, specbyte,
			  WRITEUNPACKED, fd))
	    {
		PError ("\nhp2xx -- writing PAC file");
		return ERROR;
	    }
	}
	else if (horicompr <= verticompr)
	{
	    /* horizontal compression was better, write it  */
	    if (Pack_PAC(screen, packbyte, lablbyte, specbyte,
			  WRITEHORI, fd))
	    {
		PError ("\nhp2xx -- writing PAC file");
		return ERROR;
	    }
	}
	else
	{
	    /* vertical compression was better, write it    */
	    if (Pack_PAC(screen, packbyte, lablbyte, specbyte,
			  WRITEVERTI, fd))
	    {
		PError ("\nhp2xx -- writing PAC file");
		return ERROR;
	    }
	}


	/* close file   */
	if (!pg->quiet)
	    Eprintf ("close");
	fclose(fd);

	/* line feed    */
	if (!pg->quiet)
	    Eprintf ("\n");

    }
  }

    /* final message    */
    if (!pg->quiet)
	Eprintf ("(End of PAC)\n");
  return 0;
}