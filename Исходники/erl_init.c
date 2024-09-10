void
erl_start(int argc, char **argv)
{
    int i = 1;
    char* arg=NULL;
    int have_break_handler = 1;
    char envbuf[21]; /* enough for any 64-bit integer */
    size_t envbufsz;
    int ncpu = early_init(&argc, argv);
    int proc_tab_sz = ERTS_DEFAULT_MAX_PROCESSES;
    int port_tab_sz = ERTS_DEFAULT_MAX_PORTS;
    int port_tab_sz_ignore_files = 0;
    int legacy_proc_tab = 0;
    int legacy_port_tab = 0;


    envbufsz = sizeof(envbuf);
    if (erts_sys_getenv_raw(ERL_MAX_ETS_TABLES_ENV, envbuf, &envbufsz) == 0)
	user_requested_db_max_tabs = atoi(envbuf);
    else
	user_requested_db_max_tabs = 0;

    envbufsz = sizeof(envbuf);
    if (erts_sys_getenv_raw("ERL_FULLSWEEP_AFTER", envbuf, &envbufsz) == 0) {
	Uint16 max_gen_gcs = atoi(envbuf);
	erts_smp_atomic32_set_nob(&erts_max_gen_gcs,
				  (erts_aint32_t) max_gen_gcs);
    }

    envbufsz = sizeof(envbuf);
    if (erts_sys_getenv_raw("ERL_MAX_PORTS", envbuf, &envbufsz) == 0) {
	port_tab_sz = atoi(envbuf);
	port_tab_sz_ignore_files = 1;
    }

#if (defined(__APPLE__) && defined(__MACH__)) || defined(__DARWIN__)
    /*
     * The default stack size on MacOS X is too small for pcre.
     */
    erts_sched_thread_suggested_stack_size = 256;
#endif

#ifdef DEBUG
    verbose = DEBUG_DEFAULT;
#endif

    erts_error_logger_warnings = am_error;

    while (i < argc) {
	if (argv[i][0] != '-') {
	    erts_usage();
	}
	if (strcmp(argv[i], "--") == 0) { /* end of emulator options */
	    i++;
	    break;
	}
	switch (argv[i][1]) {

	    /*
	     * NOTE: -M flags are handled (and removed from argv) by
	     * erts_alloc_init(). 
	     *
	     * The -d, -m, -S, -t, and -T flags was removed in
	     * Erlang 5.3/OTP R9C.
	     *
	     * -S, and -T has been reused in Erlang 5.5/OTP R11B.
	     *
	     * -d has been reused in a patch R12B-4.
	     */

	case '#' :
	    arg = get_arg(argv[i]+2, argv[i+1], &i);
	    if ((display_items = atoi(arg)) == 0) {
		erts_fprintf(stderr, "bad display items%s\n", arg);
		erts_usage();
	    }
	    VERBOSE(DEBUG_SYSTEM,
                    ("using display items %d\n",display_items));
	    break;
	case 'p':
	    if (!strncmp(argv[i],"-pc",3)) {
		int printable_chars = ERL_PRINTABLE_CHARACTERS_LATIN1;
		arg = get_arg(argv[i]+3, argv[i+1], &i);
		if (!strcmp(arg,"unicode")) {
		    printable_chars = ERL_PRINTABLE_CHARACTERS_UNICODE;
		} else if (strcmp(arg,"latin1")) {
		    erts_fprintf(stderr, "bad range of printable "
				 "characters: %s\n", arg);
		    erts_usage();
		}
		erts_set_printable_characters(printable_chars);
		break;
	    } else {
		erts_fprintf(stderr, "%s unknown flag %s\n", argv[0], argv[i]);
		erts_usage();
	    }
	case 'f':
	    if (!strncmp(argv[i],"-fn",3)) {
		int warning_type =  ERL_FILENAME_WARNING_WARNING;
		arg = get_arg(argv[i]+3, argv[i+1], &i);
		switch (*arg) {
		case 'u':
		    switch (*(arg+1)) {
		    case 'w':
		    case 0:
			break;
		    case 'i':
			warning_type =  ERL_FILENAME_WARNING_IGNORE;
			break;
		    case 'e':
			warning_type =  ERL_FILENAME_WARNING_ERROR;
			break;
		    default:
			erts_fprintf(stderr, "bad type of warnings for "
				     "wrongly coded filename: %s\n", arg+1);
			erts_usage();
		    }
		    erts_set_user_requested_filename_encoding
			(
			 ERL_FILENAME_UTF8,
			 warning_type
			 );
		    break;
		case 'l':
		    erts_set_user_requested_filename_encoding
			(
			 ERL_FILENAME_LATIN1,
			 warning_type
			 );
		    break;
		case 'a':
		    switch (*(arg+1)) {
		    case 'w':
		    case 0:
			break;
		    case 'i':
			warning_type =  ERL_FILENAME_WARNING_IGNORE;
			break;
		    case 'e':
			warning_type =  ERL_FILENAME_WARNING_ERROR;
			break;
		    default:
			erts_fprintf(stderr, "bad type of warnings for "
				     "wrongly coded filename: %s\n", arg+1);
			erts_usage();
		    }
		    erts_set_user_requested_filename_encoding
			(
			 ERL_FILENAME_UNKNOWN,
			 warning_type
			 );
		    break;
		default:
		    erts_fprintf(stderr, "bad filename encoding %s, can be "
				 "(l,u or a, optionally followed by w, "
				 "i or e)\n", arg);
		    erts_usage();
		}
		break;
	    } else {
		erts_fprintf(stderr, "%s unknown flag %s\n", argv[0], argv[i]);
		erts_usage();
	    }
	case 'L':
	    erts_no_line_info = 1;
	    break;
	case 'v':
#ifdef DEBUG
	    if (argv[i][2] == '\0') {
		verbose |= DEBUG_SYSTEM;
	    } else {
		char *ch;
		for (ch = argv[i]+2; *ch != '\0'; ch++) {
		    switch (*ch) {
		    case 's': verbose |= DEBUG_SYSTEM; break;
		    case 'g': verbose |= DEBUG_PRIVATE_GC; break;
		    case 'M': verbose |= DEBUG_MEMORY; break;
		    case 'a': verbose |= DEBUG_ALLOCATION; break;
		    case 't': verbose |= DEBUG_THREADS; break;
		    case 'p': verbose |= DEBUG_PROCESSES; break;
		    case 'm': verbose |= DEBUG_MESSAGES; break;
		    default : erts_fprintf(stderr,"Unknown verbose option: %c\n",*ch);
		    }
		}
	    }
            erts_printf("Verbose level: ");
            if (verbose & DEBUG_SYSTEM) erts_printf("SYSTEM ");
            if (verbose & DEBUG_PRIVATE_GC) erts_printf("PRIVATE_GC ");
            if (verbose & DEBUG_MEMORY) erts_printf("PARANOID_MEMORY ");
	    if (verbose & DEBUG_ALLOCATION) erts_printf("ALLOCATION ");
	    if (verbose & DEBUG_THREADS) erts_printf("THREADS ");
	    if (verbose & DEBUG_PROCESSES) erts_printf("PROCESSES ");
	    if (verbose & DEBUG_MESSAGES) erts_printf("MESSAGES ");
            erts_printf("\n");
#else
	    erts_fprintf(stderr, "warning: -v (only in debug compiled code)\n");
#endif
	    break;
	case 'V' :
	    {
		char tmp[256];

		tmp[0] = tmp[1] = '\0';
#ifdef DEBUG
		strcat(tmp, ",DEBUG");
#endif
#ifdef ERTS_SMP
		strcat(tmp, ",SMP");
#endif
#ifdef USE_THREADS
		strcat(tmp, ",ASYNC_THREADS");
#endif
#ifdef HIPE
		strcat(tmp, ",HIPE");
#endif
		erts_fprintf(stderr, "Erlang ");
		if (tmp[1]) {
		    erts_fprintf(stderr, "(%s) ", tmp+1);
		}
		erts_fprintf(stderr, "(" EMULATOR ") emulator version "
			   ERLANG_VERSION "\n");
		erl_exit(0, "");
	    }
	    break;

	case 'H':		/* undocumented */
	    fprintf(stderr, "The undocumented +H option has been removed (R10B-6).\n\n");
	    break;

	case 'h': {
	    char *sub_param = argv[i]+2;
	    /* set default heap size
	     *
	     * h|ms  - min_heap_size
	     * h|mbs - min_bin_vheap_size
	     *
	     */
	    if (has_prefix("mbs", sub_param)) {
		arg = get_arg(sub_param+3, argv[i+1], &i);
		if ((BIN_VH_MIN_SIZE = atoi(arg)) <= 0) {
		    erts_fprintf(stderr, "bad heap size %s\n", arg);
		    erts_usage();
		}
		VERBOSE(DEBUG_SYSTEM, ("using minimum binary virtual heap size %d\n", BIN_VH_MIN_SIZE));

	    } else if (has_prefix("ms", sub_param)) {
		arg = get_arg(sub_param+2, argv[i+1], &i);
		if ((H_MIN_SIZE = atoi(arg)) <= 0) {
		    erts_fprintf(stderr, "bad heap size %s\n", arg);
		    erts_usage();
		}
		VERBOSE(DEBUG_SYSTEM, ("using minimum heap size %d\n", H_MIN_SIZE));
	    } else {
	        /* backward compatibility */
		arg = get_arg(argv[i]+2, argv[i+1], &i);
		if ((H_MIN_SIZE = atoi(arg)) <= 0) {
		    erts_fprintf(stderr, "bad heap size %s\n", arg);
		    erts_usage();
		}
		VERBOSE(DEBUG_SYSTEM, ("using minimum heap size %d\n", H_MIN_SIZE));
	    }
	    break;
	}
	case 'd':
	    /*
	     * Never produce crash dumps for internally detected
	     * errors; only produce a core dump. (Generation of
	     * crash dumps is destructive and makes it impossible
	     * to inspect the contents of process heaps in the
	     * core dump.)
	     */
	    erts_no_crash_dump = 1;
	    break;

	case 'e':
	    if (sys_strcmp("c", argv[i]+2) == 0) {
		erts_ets_always_compress = 1;
	    }
	    else {
		/* set maximum number of ets tables */
		arg = get_arg(argv[i]+2, argv[i+1], &i);
		if (( user_requested_db_max_tabs = atoi(arg) ) < 0) {
		    erts_fprintf(stderr, "bad maximum number of ets tables %s\n", arg);
		    erts_usage();
		}
		VERBOSE(DEBUG_SYSTEM,
			("using maximum number of ets tables %d\n",
			 user_requested_db_max_tabs));
	    }
	    break;

	case 'i':
	    /* define name of module for initial function */
	    init = get_arg(argv[i]+2, argv[i+1], &i);
	    break;

	case 'b':
	    /* define name of initial function */
	    boot = get_arg(argv[i]+2, argv[i+1], &i);
	    break;

	case 'B':
	  if (argv[i][2] == 'i')          /* +Bi */
	    ignore_break = 1;
	  else if (argv[i][2] == 'c')     /* +Bc */
	    replace_intr = 1;
	  else if (argv[i][2] == 'd')     /* +Bd */
	    have_break_handler = 0;
	  else if (argv[i+1][0] == 'i') { /* +B i */
	    get_arg(argv[i]+2, argv[i+1], &i);
	    ignore_break = 1;
	  }
	  else if (argv[i+1][0] == 'c') { /* +B c */
	    get_arg(argv[i]+2, argv[i+1], &i);
	    replace_intr = 1;
	  }
	  else if (argv[i+1][0] == 'd') { /* +B d */
	    get_arg(argv[i]+2, argv[i+1], &i);
	    have_break_handler = 0;
	  }
	  else			          /* +B */
	    have_break_handler = 0;
	  break;

	case 'K':
	    /* If kernel poll support is present,
	       erl_sys_args() will remove the K parameter
	       and value */
	    get_arg(argv[i]+2, argv[i+1], &i);
	    erts_fprintf(stderr,
		       "kernel-poll not supported; \"K\" parameter ignored\n",
		       arg);
	    break;

	case 'n':
	    arg = get_arg(argv[i]+2, argv[i+1], &i);
	    switch (arg[0]) {
	    case 's': /* synchronous */
		erts_port_synchronous_ops = 1;
		erts_port_schedule_all_ops = 0;
		break;
	    case 'a': /* asynchronous */
		erts_port_synchronous_ops = 0;
		erts_port_schedule_all_ops = 1;
		break;
	    case 'd': /* Default - schedule on conflict (asynchronous) */
		erts_port_synchronous_ops = 0;
		erts_port_schedule_all_ops = 0;
		break;
	    default:
	    bad_n_option:
		erts_fprintf(stderr, "bad -n option %s\n", arg);
		erts_usage();
	    }
	    if (arg[1] != '\0')
		goto bad_n_option;
	    break;

	case 'P': /* set maximum number of processes */
	    arg = get_arg(argv[i]+2, argv[i+1], &i);
	    if (strcmp(arg, "legacy") == 0)
		legacy_proc_tab = 1;
	    else {
		errno = 0;
		proc_tab_sz = strtol(arg, NULL, 10);
		if (errno != 0
		    || proc_tab_sz < ERTS_MIN_PROCESSES
		    || ERTS_MAX_PROCESSES < proc_tab_sz) {
		    erts_fprintf(stderr, "bad number of processes %s\n", arg);
		    erts_usage();
		}
	    }
	    break;

	case 'Q': /* set maximum number of ports */
	    arg = get_arg(argv[i]+2, argv[i+1], &i);
	    if (strcmp(arg, "legacy") == 0)
		legacy_port_tab = 1;
	    else {
		errno = 0;
		port_tab_sz = strtol(arg, NULL, 10);
		if (errno != 0
		    || port_tab_sz < ERTS_MIN_PROCESSES
		    || ERTS_MAX_PROCESSES < port_tab_sz) {
		    erts_fprintf(stderr, "bad number of ports %s\n", arg);
		    erts_usage();
		}
		port_tab_sz_ignore_files = 1;
	    }
	    break;

	case 'S' : /* Was handled in early_init() just read past it */
	    (void) get_arg(argv[i]+2, argv[i+1], &i);
	    break;

	case 's' : {
	    char *estr;
	    int res;
	    char *sub_param = argv[i]+2;
	    if (has_prefix("bt", sub_param)) {
		arg = get_arg(sub_param+2, argv[i+1], &i);
		res = erts_init_scheduler_bind_type_string(arg);
		if (res != ERTS_INIT_SCHED_BIND_TYPE_SUCCESS) {
		    switch (res) {
		    case ERTS_INIT_SCHED_BIND_TYPE_NOT_SUPPORTED:
			estr = "not supported";
			break;
		    case ERTS_INIT_SCHED_BIND_TYPE_ERROR_NO_CPU_TOPOLOGY:
			estr = "no cpu topology available";
			break;
		    case ERTS_INIT_SCHED_BIND_TYPE_ERROR_BAD_TYPE:
			estr = "invalid type";
			break;
		    default:
			estr = "undefined error";
			break;
		    }
		    erts_fprintf(stderr,
				 "setting scheduler bind type '%s' failed: %s\n",
				 arg,
				 estr);
		    erts_usage();
		}
	    }
	    else if (has_prefix("bwt", sub_param)) {
		arg = get_arg(sub_param+3, argv[i+1], &i);
		if (erts_sched_set_busy_wait_threshold(arg) != 0) {
		    erts_fprintf(stderr, "bad scheduler busy wait threshold: %s\n",
				 arg);
		    erts_usage();
		}
		VERBOSE(DEBUG_SYSTEM,
			("scheduler wakup threshold: %s\n", arg));
	    }
	    else if (has_prefix("cl", sub_param)) {
		arg = get_arg(sub_param+2, argv[i+1], &i);
		if (sys_strcmp("true", arg) == 0)
		    erts_sched_compact_load = 1;
		else if (sys_strcmp("false", arg) == 0)
		    erts_sched_compact_load = 0;
		else {
		    erts_fprintf(stderr,
				 "bad scheduler compact load value '%s'\n",
				 arg);
		    erts_usage();
		}
	    }
	    else if (has_prefix("ct", sub_param)) {
		arg = get_arg(sub_param+2, argv[i+1], &i);
		res = erts_init_cpu_topology_string(arg);
		if (res != ERTS_INIT_CPU_TOPOLOGY_OK) {
		    switch (res) {
		    case ERTS_INIT_CPU_TOPOLOGY_INVALID_ID:
			estr = "invalid identifier";
			break;
		    case ERTS_INIT_CPU_TOPOLOGY_INVALID_ID_RANGE:
			estr = "invalid identifier range";
			break;
		    case ERTS_INIT_CPU_TOPOLOGY_INVALID_HIERARCHY:
			estr = "invalid hierarchy";
			break;
		    case ERTS_INIT_CPU_TOPOLOGY_INVALID_ID_TYPE:
			estr = "invalid identifier type";
			break;
		    case ERTS_INIT_CPU_TOPOLOGY_INVALID_NODES:
			estr = "invalid nodes declaration";
			break;
		    case ERTS_INIT_CPU_TOPOLOGY_MISSING_LID:
			estr = "missing logical identifier";
			break;
		    case ERTS_INIT_CPU_TOPOLOGY_NOT_UNIQUE_LIDS:
			estr = "not unique logical identifiers";
			break;
		    case ERTS_INIT_CPU_TOPOLOGY_NOT_UNIQUE_ENTITIES:
			estr = "not unique entities";
			break;
		    case ERTS_INIT_CPU_TOPOLOGY_MISSING:
			estr = "missing cpu topology";
			break;
		    default:
			estr = "undefined error";
			break;
		    }
		    erts_fprintf(stderr,
				 "bad cpu topology '%s': %s\n",
				 arg,
				 estr);
		    erts_usage();
		}
	    }
	    else if (has_prefix("pp", sub_param)) {
		arg = get_arg(sub_param+2, argv[i+1], &i);
		if (sys_strcmp(arg, "true") == 0)
		    erts_port_parallelism = 1;
		else if (sys_strcmp(arg, "false") == 0)
		    erts_port_parallelism = 0;
		else {
		    erts_fprintf(stderr,
				 "bad port parallelism scheduling hint %s\n",
				 arg);
		    erts_usage();
		}
	    }
	    else if (sys_strcmp("nsp", sub_param) == 0)
		erts_use_sender_punish = 0;
	    else if (has_prefix("tbt", sub_param)) {
		arg = get_arg(sub_param+3, argv[i+1], &i);
		res = erts_init_scheduler_bind_type_string(arg);
		if (res == ERTS_INIT_SCHED_BIND_TYPE_ERROR_BAD_TYPE) {
		    erts_fprintf(stderr,
				 "setting scheduler bind type '%s' failed: invalid type\n",
				 arg);
		    erts_usage();
		}
	    }
	    else if (has_prefix("wct", sub_param)) {
		arg = get_arg(sub_param+3, argv[i+1], &i);
		if (erts_sched_set_wake_cleanup_threshold(arg) != 0) {
		    erts_fprintf(stderr, "scheduler wake cleanup threshold: %s\n",
				 arg);
		    erts_usage();
		}
		VERBOSE(DEBUG_SYSTEM,
			("scheduler wake cleanup threshold: %s\n", arg));
	    }
	    else if (has_prefix("wt", sub_param)) {
		arg = get_arg(sub_param+2, argv[i+1], &i);
		if (erts_sched_set_wakeup_other_thresold(arg) != 0) {
		    erts_fprintf(stderr, "scheduler wakeup threshold: %s\n",
				 arg);
		    erts_usage();
		}
		VERBOSE(DEBUG_SYSTEM,
			("scheduler wakeup threshold: %s\n", arg));
	    }
	    else if (has_prefix("ws", sub_param)) {
		arg = get_arg(sub_param+2, argv[i+1], &i);
		if (erts_sched_set_wakeup_other_type(arg) != 0) {
		    erts_fprintf(stderr, "scheduler wakeup strategy: %s\n",
				 arg);
		    erts_usage();
		}
		VERBOSE(DEBUG_SYSTEM,
			("scheduler wakeup threshold: %s\n", arg));
	    }
	    else if (has_prefix("ss", sub_param)) {
		/* suggested stack size (Kilo Words) for scheduler threads */
		arg = get_arg(sub_param+2, argv[i+1], &i);
		erts_sched_thread_suggested_stack_size = atoi(arg);

		if ((erts_sched_thread_suggested_stack_size
		     < ERTS_SCHED_THREAD_MIN_STACK_SIZE)
		    || (erts_sched_thread_suggested_stack_size >
			ERTS_SCHED_THREAD_MAX_STACK_SIZE)) {
		    erts_fprintf(stderr, "bad stack size for scheduler threads %s\n",
				 arg);
		    erts_usage();
		}
		VERBOSE(DEBUG_SYSTEM,
			("suggested scheduler thread stack size %d kilo words\n",
			 erts_sched_thread_suggested_stack_size));
	    }
	    else if (has_prefix("fwi", sub_param)) {
		long val;
		arg = get_arg(sub_param+3, argv[i+1], &i);
		errno = 0;
		val = strtol(arg, NULL, 10);
		if (errno != 0 || val < 0) {
		    erts_fprintf(stderr,
				 "bad scheduler forced wakeup "
				 "interval %s\n",
				 arg);
		    erts_usage();
		}
#ifdef ERTS_SMP
		erts_runq_supervision_interval = val;
#endif
	    }
	    else {
		erts_fprintf(stderr, "bad scheduling option %s\n", argv[i]);
		erts_usage();
	    }
	    break;
	}
	case 't':
	    /* set atom table size */
	    arg = get_arg(argv[i]+2, argv[i+1], &i);
	    errno = 0;
	    erts_atom_table_size = strtol(arg, NULL, 10);
	    if (errno != 0 ||
		erts_atom_table_size < MIN_ATOM_TABLE_SIZE ||
		erts_atom_table_size > MAX_ATOM_TABLE_SIZE) {
		erts_fprintf(stderr, "bad atom table size %s\n", arg);
		erts_usage();
	    }
	    VERBOSE(DEBUG_SYSTEM,
                    ("setting maximum number of atoms to %d\n",
		     erts_atom_table_size));
	    break;

	case 'T' :
	    arg = get_arg(argv[i]+2, argv[i+1], &i);
	    errno = 0;
	    erts_modified_timing_level = atoi(arg);
	    if ((erts_modified_timing_level == 0 && errno != 0)
		|| erts_modified_timing_level < 0
		|| erts_modified_timing_level >= ERTS_MODIFIED_TIMING_LEVELS) {
		erts_fprintf(stderr, "bad modified timing level %s\n", arg);
		erts_usage();
	    }
	    else {
		VERBOSE(DEBUG_SYSTEM,
			("using modified timing level %d\n",
			 erts_modified_timing_level));
	    }

	    break;

	case 'R': {
	    /* set compatibility release */
	    int this_rel;

	    arg = get_arg(argv[i]+2, argv[i+1], &i);
	    erts_compat_rel = atoi(arg);

	    this_rel = this_rel_num();
	    if (erts_compat_rel < this_rel - 2 || this_rel < erts_compat_rel) {
		erts_fprintf(stderr, "bad compatibility release number %s\n", arg);
		erts_usage();
	    }

	    switch (erts_compat_rel) {
		/* Currently no compat features... */
	    default:
		break;
	    }

	    break;
	}

	case 'A': /* Was handled in early init just read past it */
	    (void) get_arg(argv[i]+2, argv[i+1], &i);
	    break;

	case 'a':
	    /* suggested stack size (Kilo Words) for threads in thread pool */
	    arg = get_arg(argv[i]+2, argv[i+1], &i);
	    erts_async_thread_suggested_stack_size = atoi(arg);
	    
	    if ((erts_async_thread_suggested_stack_size
		 < ERTS_ASYNC_THREAD_MIN_STACK_SIZE)
		|| (erts_async_thread_suggested_stack_size >
		    ERTS_ASYNC_THREAD_MAX_STACK_SIZE)) {
		erts_fprintf(stderr, "bad stack size for async threads %s\n",
			     arg);
		erts_usage();
	    }

	    VERBOSE(DEBUG_SYSTEM,
		    ("suggested async-thread stack size %d kilo words\n",
		     erts_async_thread_suggested_stack_size));
	    break;

	case 'r': {
	    char *sub_param = argv[i]+2;
	    if (has_prefix("g", sub_param)) {
		get_arg(sub_param+1, argv[i+1], &i);
		/* already handled */
	    }
	    else {
		erts_ets_realloc_always_moves = 1;
	    }
	    break;
	}
	case 'c':
	    if (argv[i][2] == 0) { /* -c: documented option */
		erts_disable_tolerant_timeofday = 1;
	    }
#ifdef ERTS_OPCODE_COUNTER_SUPPORT
	    else if (argv[i][2] == 'i') { /* -ci: undcoumented option*/
		count_instructions = 1;
	    }
#endif
	    break;
	case 'W':
	    arg = get_arg(argv[i]+2, argv[i+1], &i);
	    switch (arg[0]) {
	    case 'i':
		erts_error_logger_warnings = am_info;
		break;
	    case 'w':
		erts_error_logger_warnings = am_warning;
		break;
	    case 'e': /* The default */
		erts_error_logger_warnings = am_error;
	    default:
		erts_fprintf(stderr, "unrecognized warning_map option %s\n", arg);
		erts_usage();
	    }
	    break;

	case 'z': {
	    char *sub_param = argv[i]+2;
	    int new_limit;

	    if (has_prefix("dbbl", sub_param)) {
		arg = get_arg(sub_param+4, argv[i+1], &i);
		new_limit = atoi(arg);
		if (new_limit < 1 || INT_MAX/1024 < new_limit) {
		    erts_fprintf(stderr, "Invalid dbbl limit: %d\n", new_limit);
		    erts_usage();
		} else {
		    erts_dist_buf_busy_limit = new_limit*1024;
		}
	    } else {
		erts_fprintf(stderr, "bad -z option %s\n", argv[i]);
		erts_usage();
	    }
	    break;
        }

	default:
	    erts_fprintf(stderr, "%s unknown flag %s\n", argv[0], argv[i]);
	    erts_usage();
	}
	i++;
    }

/* Output format on windows for sprintf defaults to three exponents.
 * We use two-exponent to mimic normal sprintf behaviour.
 */

#if defined(__WIN32__) && defined(_TWO_DIGIT_EXPONENT)
    _set_output_format(_TWO_DIGIT_EXPONENT);
#endif

   /* Restart will not reinstall the break handler */
#ifdef __WIN32__
    if (ignore_break)
	erts_set_ignore_break();
    else if (replace_intr)
	erts_replace_intr();
    else
	init_break_handler();
#else
    if (ignore_break)
	erts_set_ignore_break();
    else if (have_break_handler)
	init_break_handler();
    if (replace_intr)
	erts_replace_intr();
#endif

    boot_argc = argc - i;  /* Number of arguments to init */
    boot_argv = &argv[i];

    erl_init(ncpu,
	     proc_tab_sz,
	     legacy_proc_tab,
	     port_tab_sz,
	     port_tab_sz_ignore_files,
	     legacy_port_tab);

    load_preloaded();
    erts_end_staging_code_ix();
    erts_commit_staging_code_ix();

    erts_initialized = 1;

    erl_first_process_otp("otp_ring0", NULL, 0, boot_argc, boot_argv);

#ifdef ERTS_SMP
    erts_start_schedulers();
    /* Let system specific code decide what to do with the main thread... */

    erts_sys_main_thread(); /* May or may not return! */
#else
    erts_thr_set_main_status(1, 1);
#if ERTS_USE_ASYNC_READY_Q
    erts_get_scheduler_data()->aux_work_data.async_ready.queue
	= erts_get_async_ready_queue(1);
#endif
    set_main_stack_size();
    process_main();
#endif
}