int main(int argc, char **argv)
{
	sigset_t set;
	InterfaceName *ifname;
	int sig;

	bool syntonize = false;
	int i;
	bool pps = false;
	uint8_t priority1 = 248;

	int restorefd = -1;
	void *restoredata = ((void *) -1);
	char *restoredataptr = NULL;
	off_t restoredatalength;
	off_t restoredatacount;
	bool restorefailed = false;
	LinuxIPCArg *ipc_arg = NULL;
	
	int accelerated_sync_count = 0;
    
	LinuxNetworkInterfaceFactory *default_factory =
		new LinuxNetworkInterfaceFactory;
	OSNetworkInterfaceFactory::registerFactory
		(factory_name_t("default"), default_factory);
	LinuxThreadFactory *thread_factory = new LinuxThreadFactory();
	LinuxTimerQueueFactory *timerq_factory = new LinuxTimerQueueFactory();
	LinuxLockFactory *lock_factory = new LinuxLockFactory();
	LinuxTimerFactory *timer_factory = new LinuxTimerFactory();
	LinuxConditionFactory *condition_factory = new LinuxConditionFactory();
	LinuxSharedMemoryIPC *ipc = new LinuxSharedMemoryIPC();
	/* Create Low level network interface object */
	if( argc < 2 ) {
		printf( "Interface name required\n" );
		print_usage( argv[0] );
		return -1;
	}
	ifname = new InterfaceName( argv[1], strlen(argv[1]) ); 

	/* Process optional arguments */
	for( i = 2; i < argc; ++i ) {
		if( argv[i][0] == '-' ) {
			if( toupper( argv[i][1] ) == 'S' ) {
				// Get syntonize directive from command line
				syntonize = true;
			}
			else if( toupper( argv[i][1] ) == 'F' ) {
				// Open file
				if( i+1 < argc ) {
					restorefd = open
						( argv[i], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR ); ++i;
					if( restorefd == -1 ) printf
						( "Failed to open restore file\n" );
				} else {
					printf( "Restore file must be specified on "
							"command line\n" );
				}
			}
			else if( toupper( argv[i][1] ) == 'A' ) {
				if( i+1 < argc ) {
					accelerated_sync_count = atoi( argv[++i] );
				} else {
					printf( "Accelerated sync count must be specified on the "
							"command line with A option\n" );
				}
			}
			else if( toupper( argv[i][1] ) == 'G' ) {
				if( i+1 < argc ) {
					ipc_arg = new LinuxIPCArg(argv[++i]);
				} else {
					printf( "Must specify group name on the command line\n" );
				}
			}
			else if( toupper( argv[i][1] ) == 'P' ) {
				pps = true;
			}
			else if( toupper( argv[i][1] ) == 'H' ) {
				print_usage( argv[0] );
				_exit(0);
			}
			else if( toupper( argv[i][1] ) == 'R' ) {
				if( i+1 >= argc ) {
					printf( "Priority 1 value must be specified on "
							"command line, using default value\n" );
				} else {
					unsigned long tmp = strtoul( argv[i+1], NULL, 0 ); ++i;
					if( tmp > 254 ) {
						printf( "Invalid priority 1 value, using "
								"default value\n" );
					} else {
						priority1 = (uint8_t) tmp;
					}
				}
			}
		}
	}
    
	if( !ipc->init( ipc_arg ) ) {
	  delete ipc;
	  ipc = NULL;
	}
	if( ipc_arg != NULL ) delete ipc_arg;
	
	if( restorefd != -1 ) {
		// MMAP file
		struct stat stat0;
		if( fstat( restorefd, &stat0 ) == -1 ) {
			printf( "Failed to stat restore file, %s\n", strerror( errno ));
		} else {
			restoredatalength = stat0.st_size;
			if( restoredatalength != 0 ) {
				if(( restoredata = mmap( NULL, restoredatalength,
										 PROT_READ | PROT_WRITE, MAP_SHARED,
										 restorefd, 0 )) == ((void *)-1) ) {
					printf( "Failed to mmap restore file, %s\n",
							strerror( errno ));
				} else {
					restoredatacount = restoredatalength;
					restoredataptr = (char *) restoredata;
				}
			}
		}
	}
	
	if (argc < 2)
		return -1;
	ifname = new InterfaceName(argv[1], strlen(argv[1]));

	HWTimestamper *timestamper = new LinuxTimestamper();
	IEEE1588Clock *clock =
	  new IEEE1588Clock( false, syntonize, priority1, timestamper,
			     timerq_factory , ipc );
	if( restoredataptr != NULL ) {
	  if( !restorefailed )
	    restorefailed =
	      !clock->restoreSerializedState( restoredataptr, 
					      &restoredatacount );
	  restoredataptr = ((char *)restoredata) +
	    (restoredatalength - restoredatacount);
	}

    IEEE1588Port *port =
      new IEEE1588Port
      ( clock, 1, false, accelerated_sync_count, timestamper, 0, ifname,
	condition_factory, thread_factory, timer_factory, lock_factory );
	if (!port->init_port()) {
		printf("failed to initialize port \n");
		return -1;
	}

	if( restoredataptr != NULL ) {
	  if( !restorefailed ) restorefailed =
	    !port->restoreSerializedState( restoredataptr, &restoredatacount );
	  restoredataptr = ((char *)restoredata) +
	    (restoredatalength - restoredatacount);
	}

	// Start PPS if requested
	if( pps ) {
	  if( !timestamper->HWTimestamper_PPS_start()) {
	    printf( "Failed to start pulse per second I/O\n" );
	  }
	}

	port->processEvent(POWERUP);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset( &set, SIGTERM );
	if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) {
		perror("pthread_sigmask()");
		return -1;
	}

	if (sigwait(&set, &sig) != 0) {
		perror("sigwait()");
		return -1;
	}

	fprintf(stderr, "Exiting on %d\n", sig);

	// Stop PPS if previously started
	if( pps ) {
	  if( !timestamper->HWTimestamper_PPS_stop()) {
	    printf( "Failed to stop pulse per second I/O\n" );
	  }
	}

	// If port is either master or slave, save clock and then port state
	if( restorefd != -1 ) {
	  if( port->getPortState() == PTP_MASTER ||
	      port->getPortState() == PTP_SLAVE ) {
	    off_t len;
	    restoredatacount = 0;
	    clock->serializeState( NULL, &len );
	    restoredatacount += len;
	    port->serializeState( NULL, &len );
	    restoredatacount += len;
	
	    if( restoredatacount > restoredatalength ) {
	      ftruncate( restorefd, restoredatacount );
	      if( restoredata != ((void *) -1)) {
		restoredata =
		  mremap( restoredata, restoredatalength, restoredatacount,
			  MREMAP_MAYMOVE );
	      } else {
		restoredata =
		  mmap( NULL, restoredatacount, PROT_READ | PROT_WRITE,
			MAP_SHARED, restorefd, 0 );
	      }
	      if( restoredata == ((void *) -1 )) goto remap_failed;
	      restoredatalength = restoredatacount;
	    }
	    
	    restoredataptr = (char *) restoredata;
	    clock->serializeState( restoredataptr, &restoredatacount );
	    restoredataptr = ((char *)restoredata) +
	      (restoredatalength - restoredatacount);
	    port->serializeState( restoredataptr, &restoredatacount );
	    restoredataptr = ((char *)restoredata) +
	      (restoredatalength - restoredatacount);
	  remap_failed:
	    ;;
	  }
	  
      
	  if( restoredata != ((void *) -1 ))
	    munmap( restoredata, restoredatalength );
	  close( restorefd );
	}

	if( ipc ) delete ipc;

	return 0;
}