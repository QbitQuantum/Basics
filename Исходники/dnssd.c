int					/* O - Exit status */
main(int  argc,				/* I - Number of command-line args */
     char *argv[])			/* I - Command-line arguments */
{
  const char	*name;			/* Backend name */
  cups_array_t	*devices;		/* Device array */
  cups_device_t	*device;		/* Current device */
  char		uriName[1024];		/* Unquoted fullName for URI */
#ifdef HAVE_DNSSD
  int		fd;			/* Main file descriptor */
  fd_set	input;			/* Input set for select() */
  struct timeval timeout;		/* Timeout for select() */
  DNSServiceRef	main_ref,		/* Main service reference */
		fax_ipp_ref,		/* IPP fax service reference */
		ipp_ref,		/* IPP service reference */
		ipp_tls_ref,		/* IPP w/TLS service reference */
		ipps_ref,		/* IPP service reference */
		local_fax_ipp_ref,	/* Local IPP fax service reference */
		local_ipp_ref,		/* Local IPP service reference */
		local_ipp_tls_ref,	/* Local IPP w/TLS service reference */
		local_ipps_ref,		/* Local IPP service reference */
		local_printer_ref,	/* Local LPD service reference */
		pdl_datastream_ref,	/* AppSocket service reference */
		printer_ref,		/* LPD service reference */
		riousbprint_ref;	/* Remote IO service reference */
#endif /* HAVE_DNSSD */
#ifdef HAVE_AVAHI
  AvahiClient	*client;		/* Client information */
  int		error;			/* Error code, if any */
#endif /* HAVE_AVAHI */
#if defined(HAVE_SIGACTION) && !defined(HAVE_SIGSET)
  struct sigaction action;		/* Actions for POSIX signals */
#endif /* HAVE_SIGACTION && !HAVE_SIGSET */


 /*
  * Don't buffer stderr, and catch SIGTERM...
  */

  setbuf(stderr, NULL);

#ifdef HAVE_SIGSET /* Use System V signals over POSIX to avoid bugs */
  sigset(SIGTERM, sigterm_handler);
#elif defined(HAVE_SIGACTION)
  memset(&action, 0, sizeof(action));

  sigemptyset(&action.sa_mask);
  action.sa_handler = sigterm_handler;
  sigaction(SIGTERM, &action, NULL);
#else
  signal(SIGTERM, sigterm_handler);
#endif /* HAVE_SIGSET */

 /*
  * Check command-line...
  */

  if (argc >= 6)
    exec_backend(argv);
  else if (argc != 1)
  {
    _cupsLangPrintf(stderr,
                    _("Usage: %s job-id user title copies options [file]"),
		    argv[0]);
    return (1);
  }

 /*
  * Only do discovery when run as "dnssd"...
  */

  if ((name = strrchr(argv[0], '/')) != NULL)
    name ++;
  else
    name = argv[0];

  if (strcmp(name, "dnssd"))
    return (0);

 /*
  * Create an array to track devices...
  */

  devices = cupsArrayNew((cups_array_func_t)compare_devices, NULL);

 /*
  * Browse for different kinds of printers...
  */

#ifdef HAVE_DNSSD
  if (DNSServiceCreateConnection(&main_ref) != kDNSServiceErr_NoError)
  {
    perror("ERROR: Unable to create service connection");
    return (1);
  }

  fd = DNSServiceRefSockFD(main_ref);

  fax_ipp_ref = main_ref;
  DNSServiceBrowse(&fax_ipp_ref, kDNSServiceFlagsShareConnection, 0,
                   "_fax-ipp._tcp", NULL, browse_callback, devices);

  ipp_ref = main_ref;
  DNSServiceBrowse(&ipp_ref, kDNSServiceFlagsShareConnection, 0,
                   "_ipp._tcp", NULL, browse_callback, devices);

  ipp_tls_ref = main_ref;
  DNSServiceBrowse(&ipp_tls_ref, kDNSServiceFlagsShareConnection, 0,
                   "_ipp-tls._tcp", NULL, browse_callback, devices);

  ipps_ref = main_ref;
  DNSServiceBrowse(&ipps_ref, kDNSServiceFlagsShareConnection, 0,
                   "_ipps._tcp", NULL, browse_callback, devices);

  local_fax_ipp_ref = main_ref;
  DNSServiceBrowse(&local_fax_ipp_ref, kDNSServiceFlagsShareConnection,
                   kDNSServiceInterfaceIndexLocalOnly,
		   "_fax-ipp._tcp", NULL, browse_local_callback, devices);

  local_ipp_ref = main_ref;
  DNSServiceBrowse(&local_ipp_ref, kDNSServiceFlagsShareConnection,
                   kDNSServiceInterfaceIndexLocalOnly,
		   "_ipp._tcp", NULL, browse_local_callback, devices);

  local_ipp_tls_ref = main_ref;
  DNSServiceBrowse(&local_ipp_tls_ref, kDNSServiceFlagsShareConnection,
                   kDNSServiceInterfaceIndexLocalOnly,
                   "_ipp-tls._tcp", NULL, browse_local_callback, devices);

  local_ipps_ref = main_ref;
  DNSServiceBrowse(&local_ipps_ref, kDNSServiceFlagsShareConnection,
                   kDNSServiceInterfaceIndexLocalOnly,
		   "_ipps._tcp", NULL, browse_local_callback, devices);

  local_printer_ref = main_ref;
  DNSServiceBrowse(&local_printer_ref, kDNSServiceFlagsShareConnection,
                   kDNSServiceInterfaceIndexLocalOnly,
                   "_printer._tcp", NULL, browse_local_callback, devices);

  pdl_datastream_ref = main_ref;
  DNSServiceBrowse(&pdl_datastream_ref, kDNSServiceFlagsShareConnection, 0,
                   "_pdl-datastream._tcp", NULL, browse_callback, devices);

  printer_ref = main_ref;
  DNSServiceBrowse(&printer_ref, kDNSServiceFlagsShareConnection, 0,
                   "_printer._tcp", NULL, browse_callback, devices);

  riousbprint_ref = main_ref;
  DNSServiceBrowse(&riousbprint_ref, kDNSServiceFlagsShareConnection, 0,
                   "_riousbprint._tcp", NULL, browse_callback, devices);
#endif /* HAVE_DNSSD */

#ifdef HAVE_AVAHI
  if ((simple_poll = avahi_simple_poll_new()) == NULL)
  {
    fputs("DEBUG: Unable to create Avahi simple poll object.\n", stderr);
    return (0);
  }

  avahi_simple_poll_set_func(simple_poll, poll_callback, NULL);

  client = avahi_client_new(avahi_simple_poll_get(simple_poll),
			    0, client_callback, simple_poll, &error);
  if (!client)
  {
    fputs("DEBUG: Unable to create Avahi client.\n", stderr);
    return (0);
  }

  browsers = 6;
  avahi_service_browser_new(client, AVAHI_IF_UNSPEC,
			    AVAHI_PROTO_UNSPEC,
			    "_fax-ipp._tcp", NULL, 0,
			    browse_callback, devices);
  avahi_service_browser_new(client, AVAHI_IF_UNSPEC,
			    AVAHI_PROTO_UNSPEC,
			    "_ipp._tcp", NULL, 0,
			    browse_callback, devices);
  avahi_service_browser_new(client, AVAHI_IF_UNSPEC,
			    AVAHI_PROTO_UNSPEC,
			    "_ipp-tls._tcp", NULL, 0,
			    browse_callback, devices);
  avahi_service_browser_new(client, AVAHI_IF_UNSPEC,
			    AVAHI_PROTO_UNSPEC,
			    "_ipps._tcp", NULL, 0,
			    browse_callback, devices);
  avahi_service_browser_new(client, AVAHI_IF_UNSPEC,
			    AVAHI_PROTO_UNSPEC,
			    "_pdl-datastream._tcp",
			    NULL, 0,
			    browse_callback,
			    devices);
  avahi_service_browser_new(client, AVAHI_IF_UNSPEC,
			    AVAHI_PROTO_UNSPEC,
			    "_printer._tcp", NULL, 0,
			    browse_callback, devices);
#endif /* HAVE_AVAHI */

 /*
  * Loop until we are killed...
  */

  while (!job_canceled)
  {
    int announce = 0;			/* Announce printers? */

#ifdef HAVE_DNSSD
    FD_ZERO(&input);
    FD_SET(fd, &input);

    timeout.tv_sec  = 0;
    timeout.tv_usec = 500000;

    if (select(fd + 1, &input, NULL, NULL, &timeout) < 0)
      continue;

    if (FD_ISSET(fd, &input))
    {
     /*
      * Process results of our browsing...
      */

      DNSServiceProcessResult(main_ref);
    }
    else
      announce = 1;

#elif defined(HAVE_AVAHI)
    got_data = 0;

    if ((error = avahi_simple_poll_iterate(simple_poll, 500)) > 0)
    {
     /*
      * We've been told to exit the loop.  Perhaps the connection to
      * Avahi failed.
      */

      break;
    }

    if (!got_data)
      announce = 1;
#endif /* HAVE_DNSSD */

/*    fprintf(stderr, "DEBUG: announce=%d\n", announce);*/

    if (announce)
    {
     /*
      * Announce any devices we've found...
      */

#ifdef HAVE_DNSSD
      DNSServiceErrorType status;	/* DNS query status */
#endif /* HAVE_DNSSD */
      cups_device_t *best;		/* Best matching device */
      char	device_uri[1024];	/* Device URI */
      int	count;			/* Number of queries */
      int	sent;			/* Number of sent */

      for (device = (cups_device_t *)cupsArrayFirst(devices),
               best = NULL, count = 0, sent = 0;
           device;
	   device = (cups_device_t *)cupsArrayNext(devices))
      {
        if (device->sent)
	  sent ++;

        if (device->ref)
	  count ++;

        if (!device->ref && !device->sent)
	{
	 /*
	  * Found the device, now get the TXT record(s) for it...
	  */

          if (count < 50)
	  {
	    fprintf(stderr, "DEBUG: Querying \"%s\"...\n", device->fullName);

#ifdef HAVE_DNSSD
	    device->ref = main_ref;

	    status = DNSServiceQueryRecord(&(device->ref),
				           kDNSServiceFlagsShareConnection,
				           0, device->fullName,
					   kDNSServiceType_TXT,
				           kDNSServiceClass_IN, query_callback,
				           device);
            if (status != kDNSServiceErr_NoError)
	      fprintf(stderr,
	              "ERROR: Unable to query \"%s\" for TXT records: %d\n",
	              device->fullName, status);
	              			/* Users never see this */
	    else
	      count ++;

#else
	    if ((device->ref = avahi_record_browser_new(client, AVAHI_IF_UNSPEC,
	                                                AVAHI_PROTO_UNSPEC,
	                                                device->fullName,
	                                                AVAHI_DNS_CLASS_IN,
	                                                AVAHI_DNS_TYPE_TXT,
	                                                0,
				                        query_callback,
				                        device)) == NULL)
	      fprintf(stderr,
	              "ERROR: Unable to query \"%s\" for TXT records: %s\n",
	              device->fullName,
	              avahi_strerror(avahi_client_errno(client)));
	              			/* Users never see this */
	    else
	      count ++;
#endif /* HAVE_AVAHI */
          }
	}
	else if (!device->sent)
	{
#ifdef HAVE_DNSSD
	 /*
	  * Got the TXT records, now report the device...
	  */

	  DNSServiceRefDeallocate(device->ref);
#else
          avahi_record_browser_free(device->ref);
#endif /* HAVE_DNSSD */

	  device->ref = NULL;

          if (!best)
	    best = device;
	  else if (_cups_strcasecmp(best->name, device->name) ||
	           _cups_strcasecmp(best->domain, device->domain))
          {
	    unquote(uriName, best->fullName, sizeof(uriName));

            if (best->uuid)
	      httpAssembleURIf(HTTP_URI_CODING_ALL, device_uri,
	                       sizeof(device_uri), "dnssd", NULL, uriName, 0,
			       best->cups_shared ? "/cups?uuid=%s" : "/?uuid=%s",
			       best->uuid);
	    else
	      httpAssembleURI(HTTP_URI_CODING_ALL, device_uri,
	                      sizeof(device_uri), "dnssd", NULL, uriName, 0,
			      best->cups_shared ? "/cups" : "/");

	    cupsBackendReport("network", device_uri, best->make_and_model,
	                      best->name, best->device_id, NULL);
	    best->sent = 1;
	    best       = device;

	    sent ++;
	  }
	  else if (best->priority > device->priority ||
	           (best->priority == device->priority &&
		    best->type < device->type))
          {
	    best->sent = 1;
	    best       = device;

	    sent ++;
	  }
	  else
	  {
	    device->sent = 1;

	    sent ++;
	  }
        }
      }

      if (best)
      {
	unquote(uriName, best->fullName, sizeof(uriName));

	if (best->uuid)
	  httpAssembleURIf(HTTP_URI_CODING_ALL, device_uri,
			   sizeof(device_uri), "dnssd", NULL, uriName, 0,
			   best->cups_shared ? "/cups?uuid=%s" : "/?uuid=%s",
			   best->uuid);
	else
	  httpAssembleURI(HTTP_URI_CODING_ALL, device_uri,
			  sizeof(device_uri), "dnssd", NULL, uriName, 0,
			  best->cups_shared ? "/cups" : "/");

	cupsBackendReport("network", device_uri, best->make_and_model,
			  best->name, best->device_id, NULL);
	best->sent = 1;
	sent ++;
      }

      fprintf(stderr, "DEBUG: sent=%d, count=%d\n", sent, count);

#ifdef HAVE_AVAHI
      if (sent == cupsArrayCount(devices) && browsers == 0)
#else
      if (sent == cupsArrayCount(devices))
#endif /* HAVE_AVAHI */
	break;
    }
  }

  return (CUPS_BACKEND_OK);
}