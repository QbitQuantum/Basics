int
main (int argc, char *argv[])
{
#if !defined(WIN32)
	install_sig_handler(SIGPIPE, (SIG_HANDLER)SIG_IGN );
#endif

	// initialize to read from config file
	myDistro->Init( argc, argv );
	myName = argv[0];
	config();
	dprintf_config_tool_on_error(0);

	// The arguments take two passes to process --- the first pass
	// figures out the mode, after which we can instantiate the required
	// query object.  We add implied constraints from the command line in
	// the second pass.
	firstPass (argc, argv);
	
	// if the mode has not been set, it is STARTD_NORMAL
	if (mode == MODE_NOTSET) {
		setMode (MODE_STARTD_NORMAL, 0, DEFAULT);
	}

	// instantiate query object
	if (!(query = new CondorQuery (type))) {
		dprintf_WriteOnErrorBuffer(stderr, true);
		fprintf (stderr, "Error:  Out of memory\n");
		exit (1);
	}
	// if a first-pass setMode set a mode_constraint, apply it now to the query object
	if (mode_constraint && ! explicit_format) {
		query->addANDConstraint(mode_constraint);
	}

	// set pretty print style implied by the type of entity being queried
	// but do it with default priority, so that explicitly requested options
	// can override it
	switch (type)
	{
#ifdef HAVE_EXT_POSTGRESQL
	  case QUILL_AD:
		setPPstyle(PP_QUILL_NORMAL, 0, DEFAULT);
		break;
#endif /* HAVE_EXT_POSTGRESQL */


	  case DEFRAG_AD:
		setPPstyle(PP_GENERIC_NORMAL, 0, DEFAULT);
		break;

	  case STARTD_AD:
		setPPstyle(PP_STARTD_NORMAL, 0, DEFAULT);
		break;

	  case SCHEDD_AD:
		setPPstyle(PP_SCHEDD_NORMAL, 0, DEFAULT);
		break;

	  case MASTER_AD:
		setPPstyle(PP_MASTER_NORMAL, 0, DEFAULT);
		break;

	  case CKPT_SRVR_AD:
		setPPstyle(PP_CKPT_SRVR_NORMAL, 0, DEFAULT);
		break;

	  case COLLECTOR_AD:
		setPPstyle(PP_COLLECTOR_NORMAL, 0, DEFAULT);
		break;

	  case STORAGE_AD:
		setPPstyle(PP_STORAGE_NORMAL, 0, DEFAULT);
		break;

	  case NEGOTIATOR_AD:
		setPPstyle(PP_NEGOTIATOR_NORMAL, 0, DEFAULT);
		break;

      case GRID_AD:
        setPPstyle(PP_GRID_NORMAL, 0, DEFAULT);
		break;

	  case GENERIC_AD:
		setPPstyle(PP_GENERIC, 0, DEFAULT);
		break;

	  case ANY_AD:
		setPPstyle(PP_ANY_NORMAL, 0, DEFAULT);
		break;

	  default:
		setPPstyle(PP_VERBOSE, 0, DEFAULT);
	}

	// set the constraints implied by the mode
	switch (mode) {
#ifdef HAVE_EXT_POSTGRESQL
	  case MODE_QUILL_NORMAL:
#endif /* HAVE_EXT_POSTGRESQL */

	  case MODE_DEFRAG_NORMAL:
	  case MODE_STARTD_NORMAL:
	  case MODE_MASTER_NORMAL:
	  case MODE_CKPT_SRVR_NORMAL:
	  case MODE_SCHEDD_NORMAL:
	  case MODE_SCHEDD_SUBMITTORS:
	  case MODE_COLLECTOR_NORMAL:
	  case MODE_NEGOTIATOR_NORMAL:
	  case MODE_STORAGE_NORMAL:
	  case MODE_GENERIC_NORMAL:
	  case MODE_ANY_NORMAL:
	  case MODE_GRID_NORMAL:
	  case MODE_HAD_NORMAL:
		break;

	  case MODE_OTHER:
			// tell the query object what the type we're querying is
		query->setGenericQueryType(genericType);
		free(genericType);
		genericType = NULL;
		break;

	  case MODE_STARTD_AVAIL:
			  // For now, -avail shows you machines avail to anyone.
		sprintf (buffer, "%s == \"%s\"", ATTR_STATE,
					state_to_string(unclaimed_state));
		if (diagnose) {
			printf ("Adding constraint [%s]\n", buffer);
		}
		query->addORConstraint (buffer);
		break;


	  case MODE_STARTD_RUN:
		sprintf (buffer, "%s == \"%s\"", ATTR_STATE,
					state_to_string(claimed_state));
		if (diagnose) {
			printf ("Adding constraint [%s]\n", buffer);
		}
		query->addORConstraint (buffer);
		break;

	  case MODE_STARTD_COD:
	    sprintf (buffer, "%s > 0", ATTR_NUM_COD_CLAIMS );
		if (diagnose) {
			printf ("Adding constraint [%s]\n", buffer);
		}
		query->addORConstraint (buffer);
		break;

	  default:
		break;
	}	

	if(javaMode) {
		sprintf( buffer, "%s == TRUE", ATTR_HAS_JAVA );
		if (diagnose) {
			printf ("Adding constraint [%s]\n", buffer);
		}
		query->addANDConstraint (buffer);
		
		projList.AppendArg(ATTR_HAS_JAVA);
		projList.AppendArg(ATTR_JAVA_MFLOPS);
		projList.AppendArg(ATTR_JAVA_VENDOR);
		projList.AppendArg(ATTR_JAVA_VERSION);

	}

	if(offlineMode) {
		query->addANDConstraint( "size( OfflineUniverses ) != 0" );

		projList.AppendArg( "OfflineUniverses" );

		//
		// Since we can't add a regex to a projection, explicitly list all
		// the attributes we know about.
		//

		projList.AppendArg( "HasVM" );
		projList.AppendArg( "VMOfflineReason" );
		projList.AppendArg( "VMOfflineTime" );
	}

	if(absentMode) {
	    sprintf( buffer, "%s == TRUE", ATTR_ABSENT );
	    if (diagnose) {
	        printf( "Adding constraint %s\n", buffer );
	    }
	    query->addANDConstraint( buffer );
	    
	    projList.AppendArg( ATTR_ABSENT );
	    projList.AppendArg( ATTR_LAST_HEARD_FROM );
	    projList.AppendArg( ATTR_CLASSAD_LIFETIME );
	}

	if(vmMode) {
		sprintf( buffer, "%s == TRUE", ATTR_HAS_VM);
		if (diagnose) {
			printf ("Adding constraint [%s]\n", buffer);
		}
		query->addANDConstraint (buffer);

		projList.AppendArg(ATTR_VM_TYPE);
		projList.AppendArg(ATTR_VM_MEMORY);
		projList.AppendArg(ATTR_VM_NETWORKING);
		projList.AppendArg(ATTR_VM_NETWORKING_TYPES);
		projList.AppendArg(ATTR_VM_HARDWARE_VT);
		projList.AppendArg(ATTR_VM_AVAIL_NUM);
		projList.AppendArg(ATTR_VM_ALL_GUEST_MACS);
		projList.AppendArg(ATTR_VM_ALL_GUEST_IPS);
		projList.AppendArg(ATTR_VM_GUEST_MAC);
		projList.AppendArg(ATTR_VM_GUEST_IP);

	}

	// second pass:  add regular parameters and constraints
	if (diagnose) {
		printf ("----------\n");
	}

	secondPass (argc, argv);

	// initialize the totals object
	if (ppStyle == PP_CUSTOM && using_print_format) {
		if (pmHeadFoot & HF_NOSUMMARY) ppTotalStyle = PP_CUSTOM;
	} else {
		ppTotalStyle = ppStyle;
	}
	TrackTotals	totals(ppTotalStyle);

	// fetch the query
	QueryResult q;

	if ((mode == MODE_STARTD_NORMAL) && (ppStyle == PP_STARTD_NORMAL)) {
		projList.AppendArg("Name");
		projList.AppendArg("Machine");
		projList.AppendArg("Opsys");
		projList.AppendArg("Arch");
		projList.AppendArg("State");
		projList.AppendArg("Activity");
		projList.AppendArg("LoadAvg");
		projList.AppendArg("Memory");
		projList.AppendArg("ActvtyTime");
		projList.AppendArg("MyCurrentTime");
		projList.AppendArg("EnteredCurrentActivity");
	} else if( ppStyle == PP_VERBOSE ) {
	    // Remove everything from the projection list if we're displaying
	    // the "long form" of the ads.
	    projList.Clear();
		// but if -attributes was supplied, show only those attributes
		if ( ! dashAttributes.isEmpty()) {
			const char * s;
			dashAttributes.rewind();
			while ((s = dashAttributes.next())) {
				projList.AppendArg(s);
			}
		}
	}

	if( projList.Count() > 0 ) {
		char **attr_list = projList.GetStringArray();
		query->setDesiredAttrs(attr_list);
		deleteStringArray(attr_list);
	}

	// if diagnose was requested, just print the query ad
	if (diagnose) {
		ClassAd 	queryAd;

		// print diagnostic information about inferred internal state
		setMode ((Mode) 0, 0, NULL);
		setType (NULL, 0, NULL);
		setPPstyle ((ppOption) 0, 0, DEFAULT);
		printf ("----------\n");

		q = query->getQueryAd (queryAd);
		fPrintAd (stdout, queryAd);

		printf ("----------\n");
		fprintf (stderr, "Result of making query ad was:  %d\n", q);
		exit (1);
	}

        // Address (host:port) is taken from requested pool, if given.
	char* addr = (NULL != pool) ? pool->addr() : NULL;
        Daemon* requested_daemon = pool;

        // If we're in "direct" mode, then we attempt to locate the daemon
	// associated with the requested subsystem (here encoded by value of mode)
        // In this case the host:port of pool (if given) denotes which
        // pool is being consulted
	if( direct ) {
		Daemon *d = NULL;
		switch( mode ) {
		case MODE_MASTER_NORMAL:
			d = new Daemon( DT_MASTER, direct, addr );
			break;
		case MODE_STARTD_NORMAL:
		case MODE_STARTD_AVAIL:
		case MODE_STARTD_RUN:
		case MODE_STARTD_COD:
			d = new Daemon( DT_STARTD, direct, addr );
			break;

#ifdef HAVE_EXT_POSTGRESQL
		case MODE_QUILL_NORMAL:
			d = new Daemon( DT_QUILL, direct, addr );
			break;
#endif /* HAVE_EXT_POSTGRESQL */

		case MODE_SCHEDD_NORMAL:
		case MODE_SCHEDD_SUBMITTORS:
			d = new Daemon( DT_SCHEDD, direct, addr );
			break;
		case MODE_NEGOTIATOR_NORMAL:
			d = new Daemon( DT_NEGOTIATOR, direct, addr );
			break;
		case MODE_CKPT_SRVR_NORMAL:
		case MODE_COLLECTOR_NORMAL:
		case MODE_LICENSE_NORMAL:
		case MODE_STORAGE_NORMAL:
		case MODE_GENERIC_NORMAL:
		case MODE_ANY_NORMAL:
		case MODE_OTHER:
		case MODE_GRID_NORMAL:
		case MODE_HAD_NORMAL:
				// These have to go to the collector, anyway.
			break;
		default:
            fprintf( stderr, "Error:  Illegal mode %d\n", mode );
			exit( 1 );
			break;
		}

                // Here is where we actually override 'addr', if we can obtain
                // address of the requested daemon/subsys.  If it can't be
                // located, then fail with error msg.
                // 'd' will be null (unset) if mode is one of above that must go to
                // collector (MODE_ANY_NORMAL, MODE_COLLECTOR_NORMAL, etc)
		if (NULL != d) {
			if( d->locate() ) {
				addr = d->addr();
				requested_daemon = d;
			} else {
				const char* id = d->idStr();
				if (NULL == id) id = d->name();
				dprintf_WriteOnErrorBuffer(stderr, true);
				if (NULL == id) id = "daemon";
				fprintf(stderr, "Error: Failed to locate %s\n", id);
				fprintf(stderr, "%s\n", d->error());
				exit( 1 );
			}
		}
	}

	ClassAdList result;
	CondorError errstack;
	if (NULL != ads_file) {
		MyString req; // query requirements
		q = query->getRequirements(req);
		const char * constraint = req.empty() ? NULL : req.c_str();
		if (read_classad_file(ads_file, result, constraint)) {
			q = Q_OK;
		}
	} else if (NULL != addr) {
			// this case executes if pool was provided, or if in "direct" mode with
			// subsystem that corresponds to a daemon (above).
			// Here 'addr' represents either the host:port of requested pool, or
			// alternatively the host:port of daemon associated with requested subsystem (direct mode)
		q = query->fetchAds (result, addr, &errstack);
	} else {
			// otherwise obtain list of collectors and submit query that way
		CollectorList * collectors = CollectorList::create();
		q = collectors->query (*query, result, &errstack);
		delete collectors;
	}
		

	// if any error was encountered during the query, report it and exit 
	if (Q_OK != q) {

		dprintf_WriteOnErrorBuffer(stderr, true);
			// we can always provide these messages:
		fprintf( stderr, "Error: %s\n", getStrQueryResult(q) );
		fprintf( stderr, "%s\n", errstack.getFullText(true).c_str() );

        if ((NULL != requested_daemon) && ((Q_NO_COLLECTOR_HOST == q) ||
			(requested_daemon->type() == DT_COLLECTOR)))
		{
				// Specific long message if connection to collector failed.
			const char* fullhost = requested_daemon->fullHostname();
			if (NULL == fullhost) fullhost = "<unknown_host>";
			const char* daddr = requested_daemon->addr();
			if (NULL == daddr) daddr = "<unknown>";
			char info[1000];
			sprintf(info, "%s (%s)", fullhost, daddr);
	        printNoCollectorContact( stderr, info, !expert );
        } else if ((NULL != requested_daemon) && (Q_COMMUNICATION_ERROR == q)) {
				// more helpful message for failure to connect to some daemon/subsys
			const char* id = requested_daemon->idStr();
			if (NULL == id) id = requested_daemon->name();
			if (NULL == id) id = "daemon";
			const char* daddr = requested_daemon->addr();
			if (NULL == daddr) daddr = "<unknown>";
			fprintf(stderr, "Error: Failed to contact %s at %s\n", id, daddr);
		}

		// fail
		exit (1);
	}

	if (noSort) {
		// do nothing 
	} else if (sortSpecs.empty()) {
        // default classad sorting
		result.Sort((SortFunctionType)lessThanFunc);
	} else {
        // User requested custom sorting expressions:
        // insert attributes related to custom sorting
        result.Open();
        while (ClassAd* ad = result.Next()) {
            for (vector<SortSpec>::iterator ss(sortSpecs.begin());  ss != sortSpecs.end();  ++ss) {
                ss->expr->SetParentScope(ad);
                classad::Value v;
                ss->expr->Evaluate(v);
                stringstream vs;
                // This will properly render all supported value types,
                // including undefined and error, although current semantic
                // pre-filters classads where sort expressions are undef/err:
                vs << ((v.IsStringValue())?"\"":"") << v << ((v.IsStringValue())?"\"":"");
                ad->AssignExpr(ss->keyAttr.c_str(), vs.str().c_str());
                // Save the full expr in case user wants to examine on output:
                ad->AssignExpr(ss->keyExprAttr.c_str(), ss->arg.c_str());
            }
        }
        
        result.Open();
		result.Sort((SortFunctionType)customLessThanFunc);
	}

	
	// output result
	prettyPrint (result, &totals);
	
    delete query;

	return 0;
}