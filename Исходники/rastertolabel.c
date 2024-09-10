int					/* O - Exit status */
main(int  argc,				/* I - Number of command-line arguments */
     char *argv[])			/* I - Command-line arguments */
{
  int			fd;		/* File descriptor */
  cups_raster_t		*ras;		/* Raster stream for printing */
  cups_page_header2_t	header;		/* Page header from file */
  unsigned		y;		/* Current line */
  ppd_file_t		*ppd;		/* PPD file */
  int			num_options;	/* Number of options */
  cups_option_t		*options;	/* Options */
#if defined(HAVE_SIGACTION) && !defined(HAVE_SIGSET)
  struct sigaction action;		/* Actions for POSIX signals */
#endif /* HAVE_SIGACTION && !HAVE_SIGSET */


 /*
  * Make sure status messages are not buffered...
  */

  setbuf(stderr, NULL);

 /*
  * Check command-line...
  */

  if (argc < 6 || argc > 7)
  {
   /*
    * We don't have the correct number of arguments; write an error message
    * and return.
    */

    _cupsLangPrintFilter(stderr, "ERROR",
                         _("%s job-id user title copies options [file]"),
			 "rastertolabel");
    return (1);
  }

 /*
  * Open the page stream...
  */

  if (argc == 7)
  {
    if ((fd = open(argv[6], O_RDONLY)) == -1)
    {
      _cupsLangPrintError("ERROR", _("Unable to open raster file"));
      sleep(1);
      return (1);
    }
  }
  else
    fd = 0;

  ras = cupsRasterOpen(fd, CUPS_RASTER_READ);

 /*
  * Register a signal handler to eject the current page if the
  * job is cancelled.
  */

  Canceled = 0;

#ifdef HAVE_SIGSET /* Use System V signals over POSIX to avoid bugs */
  sigset(SIGTERM, CancelJob);
#elif defined(HAVE_SIGACTION)
  memset(&action, 0, sizeof(action));

  sigemptyset(&action.sa_mask);
  action.sa_handler = CancelJob;
  sigaction(SIGTERM, &action, NULL);
#else
  signal(SIGTERM, CancelJob);
#endif /* HAVE_SIGSET */

 /*
  * Open the PPD file and apply options...
  */

  num_options = cupsParseOptions(argv[5], 0, &options);

  ppd = ppdOpenFile(getenv("PPD"));
  if (!ppd)
  {
    ppd_status_t	status;		/* PPD error */
    int			linenum;	/* Line number */

    _cupsLangPrintFilter(stderr, "ERROR",
                         _("The PPD file could not be opened."));

    status = ppdLastError(&linenum);

    fprintf(stderr, "DEBUG: %s on line %d.\n", ppdErrorString(status), linenum);

    return (1);
  }

  ppdMarkDefaults(ppd);
  cupsMarkOptions(ppd, num_options, options);

 /*
  * Initialize the print device...
  */

  Setup(ppd);

 /*
  * Process pages as needed...
  */

  Page = 0;

  while (cupsRasterReadHeader2(ras, &header))
  {
   /*
    * Write a status message with the page number and number of copies.
    */

    if (Canceled)
      break;

    Page ++;

    fprintf(stderr, "PAGE: %d 1\n", Page);
    _cupsLangPrintFilter(stderr, "INFO", _("Starting page %d."), Page);

   /*
    * Start the page...
    */

    StartPage(ppd, &header);

   /*
    * Loop for each line on the page...
    */

    for (y = 0; y < header.cupsHeight && !Canceled; y ++)
    {
     /*
      * Let the user know how far we have progressed...
      */

      if (Canceled)
	break;

      if ((y & 15) == 0)
      {
        _cupsLangPrintFilter(stderr, "INFO",
	                     _("Printing page %d, %u%% complete."),
			     Page, 100 * y / header.cupsHeight);
        fprintf(stderr, "ATTR: job-media-progress=%u\n",
		100 * y / header.cupsHeight);
      }

     /*
      * Read a line of graphics...
      */

      if (cupsRasterReadPixels(ras, Buffer, header.cupsBytesPerLine) < 1)
        break;

     /*
      * Write it to the printer...
      */

      OutputLine(ppd, &header, y);
    }

   /*
    * Eject the page...
    */

    _cupsLangPrintFilter(stderr, "INFO", _("Finished page %d."), Page);

    EndPage(ppd, &header);

    if (Canceled)
      break;
  }

 /*
  * Close the raster stream...
  */

  cupsRasterClose(ras);
  if (fd != 0)
    close(fd);

 /*
  * Close the PPD file and free the options...
  */

  ppdClose(ppd);
  cupsFreeOptions(num_options, options);

 /*
  * If no pages were printed, send an error message...
  */

  if (Page == 0)
  {
    _cupsLangPrintFilter(stderr, "ERROR", _("No pages were found."));
    return (1);
  }
  else
    return (0);
}