void
ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
    int   file_count=0;
    int   getoptch;
    int   currarg;
    extern char *optarg;
    extern int  optind;
    int   i, j;
    char  *tempch;
    int   err;

#define SLEEP_USEC  100
#ifdef WIN32
    WSADATA   WSAData;
#else

    struct timeval sleeptime;

    /* set the amount of time that we'll pause before sending a "." to the
       webmaster */

    sleeptime.tv_sec = SLEEP_USEC/1000000;
    sleeptime.tv_usec = SLEEP_USEC % 1000000;
#endif /* WIN32 */

    debugfile = stderr;

#ifdef WIN32
    MessageBeep(~0U); /* announce our existence */
    MessageBeep(~0U);
    MessageBeep(~0U);

    err = WSAStartup(MAKEWORD(1,1), &WSAData);
    if (err != 0) {
  errexit("Error in WSAStartup()\n");
    }

    atexit(sock_cleanup);

    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

    /* create semaphore in locked state */
    hSemaphore = CreateSemaphore(0, 0, 1, 0);
    if(hSemaphore == 0)
    {
  errexit("Create semaphore failed: %d", GetLastError());
    }
#endif /* WIN32 */

    memset(webserver, 0, sizeof(webserver));
    memset(webmaster, 0, sizeof(webmaster));
    memset(proxyserver, 0, sizeof(proxyserver));
    memset(connectstr, 0, sizeof(connectstr));

    /*
     * PARSE THE COMMAND LINE OPTIONS
     */

    while((getoptch = getopt(argc,argv,"P:f:t:l:p:u:R:w:c:n:sdv")) != EOF)
    {
        switch(getoptch)
        {
  case 'c':
            sprintf(connectstr, "%s", optarg);
      amclient = 1;
            printf("%s", OKSTR);     /* sent back to webmaster */
            fflush(stdout);
      break;
        case 'd':
            debug = 0; /* sumedh */
            break;
  case 'f':
      sprintf(configfile, "%s", optarg);
      break;
        case 'l':
            numloops = atoi(optarg);
            break;
        case 'n':
            numclients = atoi(optarg);
            break;
  case 'u':
      sprintf(uil_filelist, "%s", optarg);
      uil_filelist_f = 1;
      break;
  case 'p':
      portnum = atoi(optarg);
      break;
  case 's':
      savefile = 1;
      break;
        case 't':
            testtime = 60 * atoi(optarg);
            break;
  case 'v':
      verbose = 1;
      break;
        case 'w':
            havewebserver = 1;
            sprintf(webserver,"%s",optarg);
            break;
  case 'P':
      haveproxyserver = 1;
      sprintf(proxyserver, "%s", optarg);
      break;
  case 'R':
      record_all_transactions = 1;
      break;
        default:
            usage(argv[0]);
        }
    }

    returnerr("Client begins...\n");
    D_PRINTF( "Running in debug mode\n\n" );

    /* print the command line */
    for (i = 0; i < argc; i++)
  D_PRINTF( "%s ", argv[i] );
    D_PRINTF( "\n\n" );

    if(testtime && numloops)
    {
  /*
         * EITHER numloops OR testtime, BUT NOT BOTH.
         */
        usage(argv[0]);
    }

    if(havewebserver != 1)
    {
#ifdef WIN32
        /*
         * THE SERVER'S NAME MUST BE SPECIFIED
         */
        returnerr("No WWW Server specified\n");
        usage(argv[0]);
#else
  /* IF IT ISN'T, WE ASSUME LOCALHOST */
  sprintf(webserver, "%s", "localhost");
  havewebserver = 1;
#endif /* WIN32 */
    }

    currarg = optind;
    numfiles = 0;
    while(currarg != argc)
    {
       /*
        * GET THE URLS TO RETRIEVE.
        */
       if (numfiles == MAXNUMOFFILES) {
     returnerr("Maximum of %d files on the command line.\n");
     usage(argv[0]);
       }
       sscanf(argv[currarg],"%s",filelist[numfiles]);
       numfiles++;
       currarg++;
    }

    if ((numfiles != 0) && uil_filelist_f)
    {
  returnerr("Both a filelist and UIL specified.\n");
  usage(argv[0]);
    }

    if((numfiles == 0) && !(uil_filelist_f))
    {
        /*
         * AT LEAST ONE FILE MUST BE SPECIFIED
         */
  returnerr("No UIL resources or filelist specified \n");
        usage(argv[0]);
    }

    if((numloops == 0) && (testtime == 0))
    {
        /*
         * NO SPECIFIED NUMBER OF LOOPS, AND NO TEST TIME
         */
       usage(argv[0]);
    }
    if(numclients > MAXPROCSPERNODE || numclients < 1)
    {
  returnerr("Number of Clients must be between 1 and %d\n", MAXPROCSPERNODE);
  exit(1);
    }

    /* allow use of IP address */
    if(amclient) {
  if((tempch = strpbrk(connectstr,":")) == 0)
  {
      /*
       * INCORRECT FORMAT OF ConnectStr. CORRECT FORMAT IS
       * HOSTNAME:PORT OR HOST-IP:PORT
       */
      D_PRINTF( "Incorrect format %s: use hostname:port or ip_addr:port\n",
         connectstr );
      returnerr("Incorrect format %s: use host:port or ip_addr:port\n", connectstr);
      exit(1);
  } else {
      strncpy(webmaster, connectstr, tempch-connectstr);
  }
  if(resolve_addrs(webmaster, "tcp", &webmast_phe, &webmast_ppe, &webmast_addr, &webmast_type))
      exit(1);
    }

    if (haveproxyserver)
    {
  D_PRINTF( "Copying proxy %s to webserver\n", proxyserver );
  strcpy(webserver, proxyserver);
    }

    if (resolve_addrs(webserver, "tcp", &webserv_phe, &webserv_ppe, &webserv_addr, &webserv_type))
  exit(1);

    /*
     * INITIALIZE DATA
     */
    /* allocate space for dynamic arrays */
    load_file_list =
      (page_list_t *)mymalloc((MAXNUMOFPAGES)*sizeof(page_list_t));

    if (uil_filelist_f)
    {
      /* take a guess at the number of URLs in the file */
      D_PRINTF( "About to parse filelist %s\n", uil_filelist );
      number_of_pages = count_file_list(uil_filelist);
      numfiles = 1;

      /* IF WE HAVE A FILELIST, PARSE IT */
      /* allocate memory */
      D_PRINTF( "Allocating page list: %ld by %d\n",
  number_of_pages, numfiles );
      for (i=0; i<number_of_pages; i++)
  {
    for (j=0; j<MAXNUMOFFILES; j++)
      {
        load_file_list[i].servername[j] =
    (char *)mymalloc(URL_SIZE);
        load_file_list[i].filename[j] =
    (char *)mymalloc(URL_SIZE);
      }
  }

      D_PRINTF( "Parsing file list: %s\n", uil_filelist );
      parse_file_list(uil_filelist, load_file_list,
          &number_of_pages, &numfiles);
      /* free memory for pages that won't be used? */
      D_PRINTF( "Actual page list: %ld by %d\n",
  number_of_pages, MAXNUMOFFILES );

      D_PRINTF( "Setting up weighting for %ld pages\n",
  number_of_pages );
      total_weight = load_percent(load_file_list, number_of_pages);
      /*      total_weight = load_percent(load_file_list, number_of_pages, pages); */
    }
    else
    {
  /* no uil file */
  number_of_pages = numfiles;
    }

    if (number_of_pages < 1)
      {
  /* no pages - exit */
  D_PRINTF( "No valid URLs found\n" );
  errexit("No valid URLs found\n");
      }

#ifndef WIN32
    /*
     * IF WE ARE TO FORK ADDITIONAL CLIENTS ON THIS MACHINE,
     * WE MUST DO IT BEFORE WE CONNECT TO THE MASTER.
     *
     * FIRST, SET UP SIGNAL HANDLING
     */
    signal(SIGCHLD, childhandler);
    for(i = 0; i < numclients; i++)
    {
      thr_create (0, 0, ClientThread, 0, THR_BOUND, 0);

      /* switch(fork())
         {
             case 0:
                 numclients = 1;
                 ClientThread(0);
                 exit(0);
                 break;
             case -1:
                 errexit("Error forking child processes\n");
                 exit(1);
             default:
                break;
         } */
      select(0,(fd_set *)0,(fd_set *)0, (fd_set *)0, &sleeptime);
    }

    /*
     * Wait for all children to exit.
     */

    while (thr_join(0, 0, 0) == 0);

    /*     for(;;)
       {
      int pid = wait((int*)0);
  if ((pid == -1) && errno == ECHILD) break;
       } */
#else
    /* start threads on NT */
    for (i = 0; i < numclients; i++)
    {
  if (_beginthread(ClientThread, 0, 0) == -1)
  {
      errexit("_beginthread failed: %d", GetLastError());
  }
    }
#endif /* WIN32 */

#ifdef WIN32
    /* wait for children to get to sync point */
    while (CounterSemaphore < numclients)
        sleep(1);
    CounterSemaphore = 0;

    /* start all children simultaneously */
    ReleaseSemaphore(hSemaphore, 1, 0);

    if (testtime) {
  sleep(testtime);
  alarmhandler(); /* signal end of test to threads */
    }

    /*
     * Wait for all threads to exit.
     */
    while (CounterSemaphore < numclients)
        sleep(1);

    CloseHandle(hSemaphore);
#endif /* WIN32 */

    return;
} /* end main() */