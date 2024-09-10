static int				/* O - Command status */
recv_print_job(
    const char    *queue,		/* I - Printer name */
    int           num_defaults,		/* I - Number of default options */
    cups_option_t *defaults)		/* I - Default options */
{
  http_t	*http;			/* HTTP connection */
  int		i;			/* Looping var */
  int		status;			/* Command status */
  int		fd;			/* Temporary file */
  FILE		*fp;			/* File pointer */
  char		filename[1024];		/* Temporary filename */
  ssize_t	bytes;			/* Bytes received */
  size_t	total;			/* Total bytes */
  char		line[256],		/* Line from file/stdin */
		command,		/* Command from line */
		*count,			/* Number of bytes */
		*name;			/* Name of file */
  const char	*job_sheets;		/* Job sheets */
  int		num_data;		/* Number of data files */
  char		control[1024],		/* Control filename */
		data[100][256],		/* Data files */
		temp[100][1024];	/* Temporary files */
  char		user[1024],		/* User name */
		title[1024],		/* Job title */
		docname[1024],		/* Document name */
		dest[256];		/* Printer/class queue */
  int		accepting,		/* printer-is-accepting */
		shared,			/* printer-is-shared */
		num_options;		/* Number of options */
  cups_option_t	*options;		/* Options */
  int		id;			/* Job ID */
  int		docnumber,		/* Current document number */
		doccount;		/* Count of documents */


 /*
  * Connect to the server...
  */

  http = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption());
  if (!http)
  {
    syslog(LOG_ERR, "Unable to connect to server: %s", strerror(errno));

    putchar(1);

    return (1);
  }

 /*
  * See if the printer is available...
  */

  num_options = get_printer(http, queue, dest, sizeof(dest), &options,
                            &accepting, &shared, NULL);

  if (num_options < 0 || !accepting || !shared)
  {
    if (dest[0])
      syslog(LOG_INFO, "Rejecting job because \"%s\" is not %s", dest,
             !accepting ? "accepting jobs" : "shared");
    else
      syslog(LOG_ERR, "Unable to get printer information for \"%s\"", queue);

    httpClose(http);

    putchar(1);

    return (1);
  }

  putchar(0);				/* OK so far... */

 /*
  * Read the request...
  */

  status   = 0;
  num_data = 0;
  fd       = -1;

  control[0] = '\0';

  while (smart_gets(line, sizeof(line), stdin) != NULL)
  {
    if (strlen(line) < 2)
    {
      status = 1;
      break;
    }

    command = line[0];
    count   = line + 1;

    for (name = count + 1; *name && !isspace(*name & 255); name ++);
    while (isspace(*name & 255))
      *name++ = '\0';

    switch (command)
    {
      default :
      case 0x01 : /* Abort */
          status = 1;
	  break;

      case 0x02 : /* Receive control file */
          if (strlen(name) < 2)
	  {
	    syslog(LOG_ERR, "Bad control file name \"%s\"", name);
	    putchar(1);
	    status = 1;
	    break;
	  }

          if (control[0])
	  {
	   /*
	    * Append to the existing control file - the LPD spec is
	    * not entirely clear, but at least the OS/2 LPD code sends
	    * multiple control files per connection...
	    */

	    if ((fd = open(control, O_WRONLY)) < 0)
	    {
	      syslog(LOG_ERR,
	             "Unable to append to temporary control file \"%s\" - %s",
        	     control, strerror(errno));
	      putchar(1);
	      status = 1;
	      break;
	    }

	    lseek(fd, 0, SEEK_END);
          }
	  else
	  {
	    if ((fd = cupsTempFd(control, sizeof(control))) < 0)
	    {
	      syslog(LOG_ERR, "Unable to open temporary control file \"%s\" - %s",
        	     control, strerror(errno));
	      putchar(1);
	      status = 1;
	      break;
	    }

	    strlcpy(filename, control, sizeof(filename));
	  }
	  break;

      case 0x03 : /* Receive data file */
          if (strlen(name) < 2)
	  {
	    syslog(LOG_ERR, "Bad data file name \"%s\"", name);
	    putchar(1);
	    status = 1;
	    break;
	  }

          if (num_data >= (int)(sizeof(data) / sizeof(data[0])))
	  {
	   /*
	    * Too many data files...
	    */

	    syslog(LOG_ERR, "Too many data files (%d)", num_data);
	    putchar(1);
	    status = 1;
	    break;
	  }

	  strlcpy(data[num_data], name, sizeof(data[0]));

          if ((fd = cupsTempFd(temp[num_data], sizeof(temp[0]))) < 0)
	  {
	    syslog(LOG_ERR, "Unable to open temporary data file \"%s\" - %s",
        	   temp[num_data], strerror(errno));
	    putchar(1);
	    status = 1;
	    break;
	  }

	  strlcpy(filename, temp[num_data], sizeof(filename));

          num_data ++;
	  break;
    }

    putchar(status);

    if (status)
      break;

   /*
    * Copy the data or control file from the client...
    */

    for (total = (size_t)strtoll(count, NULL, 10); total > 0; total -= (size_t)bytes)
    {
      if (total > sizeof(line))
        bytes = (ssize_t)sizeof(line);
      else
        bytes = (ssize_t)total;

      if ((bytes = (ssize_t)fread(line, 1, (size_t)bytes, stdin)) > 0)
        bytes = write(fd, line, (size_t)bytes);

      if (bytes < 1)
      {
	syslog(LOG_ERR, "Error while reading file - %s",
               strerror(errno));
        status = 1;
	break;
      }
    }

   /*
    * Read trailing nul...
    */

    if (!status)
    {
      if (fread(line, 1, 1, stdin) < 1)
      {
        status = 1;
	syslog(LOG_ERR, "Error while reading trailing nul - %s",
               strerror(errno));
      }
      else if (line[0])
      {
        status = 1;
	syslog(LOG_ERR, "Trailing character after file is not nul (%02X)!",
	       line[0]);
      }
    }

   /*
    * Close the file and send an acknowledgement...
    */

    close(fd);

    putchar(status);

    if (status)
      break;
  }

  if (!status)
  {
   /*
    * Process the control file and print stuff...
    */

    if ((fp = fopen(control, "rb")) == NULL)
      status = 1;
    else
    {
     /*
      * Copy the default options...
      */

      for (i = 0; i < num_defaults; i ++)
	num_options = cupsAddOption(defaults[i].name,
		                    defaults[i].value,
		                    num_options, &options);

     /*
      * Grab the job information...
      */

      title[0]   = '\0';
      user[0]    = '\0';
      docname[0] = '\0';
      doccount   = 0;

      while (smart_gets(line, sizeof(line), fp) != NULL)
      {
       /*
        * Process control lines...
	*/

	switch (line[0])
	{
	  case 'J' : /* Job name */
	      strlcpy(title, line + 1, sizeof(title));
	      break;

          case 'N' : /* Document name */
              strlcpy(docname, line + 1, sizeof(docname));
              break;

	  case 'P' : /* User identification */
	      strlcpy(user, line + 1, sizeof(user));
	      break;

	  case 'L' : /* Print banner page */
	     /*
	      * If a banner was requested and it's not overridden by a
	      * command line option and the destination's default is none
	      * then add the standard banner...
	      */

	      if (cupsGetOption("job-sheets", num_defaults, defaults) == NULL &&
        	  ((job_sheets = cupsGetOption("job-sheets", num_options,
					       options)) == NULL ||
        	   !strcmp(job_sheets, "none,none")))
	      {
		num_options = cupsAddOption("job-sheets", "standard",
		                	    num_options, &options);
	      }
	      break;

	  case 'c' : /* Plot CIF file */
	  case 'd' : /* Print DVI file */
	  case 'f' : /* Print formatted file */
	  case 'g' : /* Plot file */
	  case 'l' : /* Print file leaving control characters (raw) */
	  case 'n' : /* Print ditroff output file */
	  case 'o' : /* Print PostScript output file */
	  case 'p' : /* Print file with 'pr' format (prettyprint) */
	  case 'r' : /* File to print with FORTRAN carriage control */
	  case 't' : /* Print troff output file */
	  case 'v' : /* Print raster file */
	      doccount ++;

	      if (line[0] == 'l' &&
	          !cupsGetOption("document-format", num_options, options))
		num_options = cupsAddOption("raw", "", num_options, &options);

              if (line[0] == 'p')
		num_options = cupsAddOption("prettyprint", "", num_options,
		                	    &options);
              break;
	}

	if (status)
	  break;
      }

     /*
      * Check that we have a username...
      */

      if (!user[0])
      {
	syslog(LOG_WARNING, "No username specified by client! "
		            "Using \"anonymous\"...");
	strlcpy(user, "anonymous", sizeof(user));
      }

     /*
      * Create the job...
      */

      if ((id = create_job(http, dest, title, docname, user, num_options,
                           options)) < 0)
        status = 1;
      else
      {
       /*
	* Then print the job files...
	*/

	rewind(fp);

	docname[0] = '\0';
	docnumber  = 0;

	while (smart_gets(line, sizeof(line), fp) != NULL)
	{
	 /*
          * Process control lines...
	  */

	  switch (line[0])
	  {
	    case 'N' : /* Document name */
		strlcpy(docname, line + 1, sizeof(docname));
		break;

	    case 'c' : /* Plot CIF file */
	    case 'd' : /* Print DVI file */
	    case 'f' : /* Print formatted file */
	    case 'g' : /* Plot file */
	    case 'l' : /* Print file leaving control characters (raw) */
	    case 'n' : /* Print ditroff output file */
	    case 'o' : /* Print PostScript output file */
	    case 'p' : /* Print file with 'pr' format (prettyprint) */
	    case 'r' : /* File to print with FORTRAN carriage control */
	    case 't' : /* Print troff output file */
	    case 'v' : /* Print raster file */
               /*
		* Figure out which file we are printing...
		*/

		for (i = 0; i < num_data; i ++)
	          if (!strcmp(data[i], line + 1))
		    break;

        	if (i >= num_data)
		{
	          status = 1;
		  break;
		}

               /*
		* Send the print file...
		*/

        	docnumber ++;

        	if (print_file(http, id, temp[i], docname, user,
		               cupsGetOption("document-format", num_options,
			                     options),
	                       docnumber == doccount))
                  status = 1;
		else
	          status = 0;

		break;
	  }

	  if (status)
	    break;
	}
      }

      fclose(fp);
    }
  }

  cupsFreeOptions(num_options, options);

  httpClose(http);

 /*
  * Clean up all temporary files and return...
  */

  unlink(control);

  for (i = 0; i < num_data; i ++)
    unlink(temp[i]);

  return (status);
}