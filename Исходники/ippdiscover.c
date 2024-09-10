int					/* O - Exit status */
main(int  argc,				/* I - Number of command-line args */
     char *argv[])			/* I - Command-line arguments */
{
  int		i;			/* Looping var */
  const char	*opt,			/* Current option character */
		*name = NULL,		/* Service name */
		*type = "_ipp._tcp",	/* Service type */
		*domain = "local.";	/* Service domain */
#ifdef HAVE_DNSSD
  DNSServiceRef	ref;			/* Browsing service reference */
#endif /* HAVE_DNSSD */
#ifdef HAVE_AVAHI
  AvahiClient	*client;		/* Client information */
  int		error;			/* Error code, if any */
#endif /* HAVE_AVAHI */


  for (i = 1; i < argc; i ++)
    if (!strcmp(argv[i], "snmp"))
      snmponly = 1;
    else if (!strcmp(argv[i], "ipp"))
      ipponly = 1;
    else
    {
      puts("Usage: ./ipp-printers [{ipp | snmp}]");
      return (1);
    }

 /*
  * Create an array to track devices...
  */

  devices = cupsArrayNew((cups_array_func_t)compare_devices, NULL);

 /*
  * Browse for different kinds of printers...
  */

  if (DNSServiceCreateConnection(&main_ref) != kDNSServiceErr_NoError)
  {
    perror("ERROR: Unable to create service connection");
    return (1);
  }

  fd = DNSServiceRefSockFD(main_ref);

  ipp_ref = main_ref;
  DNSServiceBrowse(&ipp_ref, kDNSServiceFlagsShareConnection, 0,
                   "_ipp._tcp", NULL, browse_callback, devices);

 /*
  * Loop until we are killed...
  */

  progress();

  for (;;)
  {
    FD_ZERO(&input);
    FD_SET(fd, &input);

    timeout.tv_sec  = 2;
    timeout.tv_usec = 500000;

    if (select(fd + 1, &input, NULL, NULL, &timeout) <= 0)
    {
      time_t curtime = time(NULL);

      for (device = (cups_device_t *)cupsArrayFirst(devices);
           device;
	   device = (cups_device_t *)cupsArrayNext(devices))
        if (!device->got_resolve)
        {
          if (!device->ref)
            break;

          if ((curtime - device->resolve_time) > 10)
          {
            device->got_resolve = -1;
	    fprintf(stderr, "\rUnable to resolve \"%s\": timeout\n",
		    device->name);
	    progress();
	  }
          else
            break;
        }

      if (!device)
        break;
    }

    if (FD_ISSET(fd, &input))
    {
     /*
      * Process results of our browsing...
      */

      progress();
      DNSServiceProcessResult(main_ref);
    }
    else
    {
     /*
      * Query any devices we've found...
      */

      DNSServiceErrorType	status;	/* DNS query status */
      int			count;	/* Number of queries */


      for (device = (cups_device_t *)cupsArrayFirst(devices), count = 0;
           device;
	   device = (cups_device_t *)cupsArrayNext(devices))
      {
        if (!device->ref && !device->sent)
	{
	 /*
	  * Found the device, now get the TXT record(s) for it...
	  */

          if (count < 50)
	  {
	    device->resolve_time = time(NULL);
	    device->ref          = main_ref;

	    status = DNSServiceResolve(&(device->ref),
				       kDNSServiceFlagsShareConnection,
				       0, device->name, device->regtype,
				       device->domain, resolve_callback,
				       device);
            if (status != kDNSServiceErr_NoError)
            {
	      fprintf(stderr, "\rUnable to resolve \"%s\": %d\n",
	              device->name, status);
	      progress();
	    }
	    else
	      count ++;
          }
	}
	else if (!device->sent && device->got_resolve)
	{
	 /*
	  * Got the TXT records, now report the device...
	  */

	  DNSServiceRefDeallocate(device->ref);
	  device->ref  = 0;
	  device->sent = 1;
        }
      }
    }
  }

#ifndef DEBUG
  fprintf(stderr, "\rFound %d printers. Now querying for capabilities...\n",
          cupsArrayCount(devices));
#endif /* !DEBUG */

  puts("#!/bin/sh -x");
  puts("test -d results && rm -rf results");
  puts("mkdir results");
  puts("CUPS_DEBUG_LEVEL=6; export CUPS_DEBUG_LEVEL");
  puts("CUPS_DEBUG_FILTER='^(ipp|http|_ipp|_http|cupsGetResponse|cupsSend|"
       "cupsWrite|cupsDo).*'; export CUPS_DEBUG_FILTER");

  for (device = (cups_device_t *)cupsArrayFirst(devices);
       device;
       device = (cups_device_t *)cupsArrayNext(devices))
  {
    if (device->got_resolve <= 0 || device->cups_shared)
      continue;

#ifdef DEBUG
    fprintf(stderr, "Checking \"%s\" (got_resolve=%d, cups_shared=%d, uri=%s)\n",
            device->name, device->got_resolve, device->cups_shared, device->uri);
#else
    fprintf(stderr, "Checking \"%s\"...\n", device->name);
#endif /* DEBUG */

    if ((http = httpConnect(device->host, device->port)) == NULL)
    {
      fprintf(stderr, "Failed to connect to \"%s\": %s\n", device->name,
              cupsLastErrorString());
      continue;
    }

    request = ippNewRequest(IPP_GET_PRINTER_ATTRIBUTES);
    ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri", NULL,
                 device->uri);

    response = cupsDoRequest(http, request, device->rp);

    if (cupsLastError() > IPP_OK_SUBST)
      fprintf(stderr, "Failed to query \"%s\": %s\n", device->name,
              cupsLastErrorString());
    else
    {
      if ((attr = ippFindAttribute(response, "ipp-versions-supported",
				   IPP_TAG_KEYWORD)) != NULL)
      {
	version = attr->values[0].string.text;

	for (i = 1; i < attr->num_values; i ++)
	  if (strcmp(attr->values[i].string.text, version) > 0)
	    version = attr->values[i].string.text;
      }
      else
	version = "1.0";

      testfile = NULL;

      if ((attr = ippFindAttribute(response, "document-format-supported",
                                   IPP_TAG_MIMETYPE)) != NULL)
      {
       /*
        * Figure out the test file for printing, preferring PDF and PostScript
        * over JPEG and plain text...
        */

        for (i = 0; i < attr->num_values; i ++)
        {
          if (!strcasecmp(attr->values[i].string.text, "application/pdf"))
          {
            testfile = "testfile.pdf";
            break;
          }
          else if (!strcasecmp(attr->values[i].string.text,
                               "application/postscript"))
            testfile = "testfile.ps";
          else if (!strcasecmp(attr->values[i].string.text, "image/jpeg") &&
                   !testfile)
            testfile = "testfile.jpg";
          else if (!strcasecmp(attr->values[i].string.text, "text/plain") &&
                   !testfile)
            testfile = "testfile.txt";
          else if (!strcasecmp(attr->values[i].string.text,
                               "application/vnd.hp-PCL") && !testfile)
            testfile = "testfile.pcl";
        }

        if (!testfile)
        {
          fprintf(stderr,
                  "Printer \"%s\" reports the following IPP file formats:\n",
                  device->name);
          for (i = 0; i < attr->num_values; i ++)
            fprintf(stderr, "    \"%s\"\n", attr->values[i].string.text);
        }
      }

      if (!testfile && device->pdl)
      {
	char	*pdl,			/* Copy of pdl string */
		*start, *end;		/* Pointers into pdl string */


        pdl = strdup(device->pdl);
	for (start = device->pdl; start && *start; start = end)
	{
	  if ((end = strchr(start, ',')) != NULL)
	    *end++ = '\0';

	  if (!strcasecmp(start, "application/pdf"))
	  {
	    testfile = "testfile.pdf";
	    break;
	  }
	  else if (!strcasecmp(start, "application/postscript"))
	    testfile = "testfile.ps";
	  else if (!strcasecmp(start, "image/jpeg") && !testfile)
	    testfile = "testfile.jpg";
	  else if (!strcasecmp(start, "text/plain") && !testfile)
	    testfile = "testfile.txt";
	  else if (!strcasecmp(start, "application/vnd.hp-PCL") && !testfile)
	    testfile = "testfile.pcl";
	}
	free(pdl);

        if (testfile)
        {
	  fprintf(stderr,
		  "Using \"%s\" for printer \"%s\" based on TXT record pdl "
		  "info.\n", testfile, device->name);
        }
        else
        {
	  fprintf(stderr,
		  "Printer \"%s\" reports the following TXT file formats:\n",
		  device->name);
	  fprintf(stderr, "    \"%s\"\n", device->pdl);
	}
      }

      if (!device->ty &&
	  (attr = ippFindAttribute(response, "printer-make-and-model",
				   IPP_TAG_TEXT)) != NULL)
	device->ty = strdup(attr->values[0].string.text);

      if (strcmp(version, "1.0") && testfile && device->ty)
      {
	char		filename[1024],	/* Filename */
			*fileptr;	/* Pointer into filename */
	const char	*typtr;		/* Pointer into ty */

        if (!strncasecmp(device->ty, "DeskJet", 7) ||
            !strncasecmp(device->ty, "DesignJet", 9) ||
            !strncasecmp(device->ty, "OfficeJet", 9) ||
            !strncasecmp(device->ty, "Photosmart", 10))
          strlcpy(filename, "HP_", sizeof(filename));
        else
          filename[0] = '\0';

	fileptr = filename + strlen(filename);

        if (!strncasecmp(device->ty, "Lexmark International Lexmark", 29))
          typtr = device->ty + 22;
        else
          typtr = device->ty;

	while (*typtr && fileptr < (filename + sizeof(filename) - 1))
	{
	  if (isalnum(*typtr & 255) || *typtr == '-')
	    *fileptr++ = *typtr++;
	  else
	  {
	    *fileptr++ = '_';
	    typtr++;
	  }
	}

	*fileptr = '\0';

        printf("# %s\n", device->name);
        printf("echo \"Testing %s...\"\n", device->name);

        if (!ipponly)
        {
	  printf("echo \"snmpwalk -c public -v 1 -Cc %s 1.3.6.1.2.1.25 "
	         "1.3.6.1.2.1.43 1.3.6.1.4.1.2699.1\" > results/%s.snmpwalk\n",
	         device->host, filename);
	  printf("snmpwalk -c public -v 1 -Cc %s 1.3.6.1.2.1.25 "
	         "1.3.6.1.2.1.43 1.3.6.1.4.1.2699.1 | "
	         "tee -a results/%s.snmpwalk\n",
	         device->host, filename);
        }

        if (!snmponly)
        {
	  printf("echo \"./ipptool-static -tIf %s -T 30 -d NOPRINT=1 -V %s %s "
	         "ipp-%s.test\" > results/%s.log\n", testfile, version,
	         device->uri, version, filename);
	  printf("CUPS_DEBUG_LOG=results/%s.debug_log "
	         "./ipptool-static -tIf %s -T 30 -d NOPRINT=1 -V %s %s "
	         "ipp-%s.test | tee -a results/%s.log\n", filename,
	         testfile, version, device->uri,
	         version, filename);
        }

	puts("");
      }
      else if (!device->ty)
	fprintf(stderr,
		"Ignoring \"%s\" since it doesn't provide a make and model.\n",
		device->name);
      else if (!testfile)
	fprintf(stderr,
	        "Ignoring \"%s\" since it does not support a common format.\n",
		device->name);
      else
	fprintf(stderr, "Ignoring \"%s\" since it only supports IPP/1.0.\n",
		device->name);
    }

    ippDelete(response);
    httpClose(http);
  }

  return (0);
}