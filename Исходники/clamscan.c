int main(int argc, char **argv)
{
	int ds, dms, ret;
	double mb, rmb;
	struct timeval t1, t2;
#ifndef C_WINDOWS
	struct timezone tz;
	sigset_t sigset;
#endif
	struct optstruct *opts;
	const struct optstruct *opt;

#if defined(C_WINDOWS) && defined(CL_THREAD_SAFE)
    if(!pthread_win32_process_attach_np()) {
	mprintf("!Can't start the win32 pthreads layer\n");
	return 72;
    }
#endif

#if !defined(C_WINDOWS) && !defined(C_BEOS)
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGXFSZ);
    sigprocmask(SIG_SETMASK, &sigset, NULL);
#endif


    if((opts = optparse(NULL, argc, argv, 1, OPT_CLAMSCAN, 0, NULL)) == NULL) {
	mprintf("!Can't parse command line options\n");
	return 40;
    }

    if(optget(opts, "verbose")->enabled) {
	mprintf_verbose = 1;
	logg_verbose = 1;
    }

    if(optget(opts, "quiet")->enabled)
	mprintf_quiet = 1;

    if(optget(opts, "stdout")->enabled)
	mprintf_stdout = 1;


    if(optget(opts, "debug")->enabled) {
#if defined(C_LINUX)
	    /* [email protected]: create a dump if needed */
	    struct rlimit rlim;

	rlim.rlim_cur = rlim.rlim_max = RLIM_INFINITY;
	if(setrlimit(RLIMIT_CORE, &rlim) < 0)
	    perror("setrlimit");
#endif
	cl_debug(); /* enable debug messages */
    }

    if(optget(opts, "version")->enabled) {
	print_version(optget(opts, "database")->strarg);
	optfree(opts);
	return 0;
    }

    if(optget(opts, "help")->enabled) {
	optfree(opts);
    	help();
	return 0;
    }

    if(optget(opts, "recursive")->enabled)
	recursion = 1;

    if(optget(opts, "infected")->enabled)
	printinfected = 1;

    if(optget(opts, "bell")->enabled)
	bell = 1;

    /* initialize logger */
    if((opt = optget(opts, "log"))->enabled) {
	logg_file = opt->strarg;
	if(logg("#\n-------------------------------------------------------------------------------\n\n")) {
	    mprintf("!Problem with internal logger.\n");
	    optfree(opts);
	    return 62;
	}
    } else 
	logg_file = NULL;

    if(actsetup(opts)) {
	optfree(opts);
	logg_close();
	exit(2);
    }

    memset(&info, 0, sizeof(struct s_info));

#ifdef C_WINDOWS
    _set_fmode(_O_BINARY);
#ifdef CL_DEBUG
    {
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
    }
#endif	
    gettimeofday(&t1, NULL);
#else
    gettimeofday(&t1, &tz);
#endif

    ret = scanmanager(opts);

    if(!optget(opts, "no-summary")->enabled) {
#ifdef C_WINDOWS
	gettimeofday(&t2, NULL);
#else
	gettimeofday(&t2, &tz);
#endif
	ds = t2.tv_sec - t1.tv_sec;
	dms = t2.tv_usec - t1.tv_usec;
	ds -= (dms < 0) ? (1):(0);
	dms += (dms < 0) ? (1000000):(0);
	logg("\n----------- SCAN SUMMARY -----------\n");
	logg("Known viruses: %u\n", info.sigs);
	logg("Engine version: %s\n", get_version());
	logg("Scanned directories: %u\n", info.dirs);
	logg("Scanned files: %u\n", info.files);
	logg("Infected files: %u\n", info.ifiles);
	if(notremoved) {
	    logg("Not removed: %u\n", notremoved);
	}
	if(notmoved) {
	    logg("Not %s: %u\n", optget(opts, "copy")->enabled ? "moved" : "copied", notmoved);
	}
	mb = info.blocks * (CL_COUNT_PRECISION / 1024) / 1024.0;
	logg("Data scanned: %2.2lf MB\n", mb);
	rmb = info.rblocks * (CL_COUNT_PRECISION / 1024) / 1024.0;
	logg("Data read: %2.2lf MB (ratio %.2f:1)\n", rmb, info.rblocks ? (double)info.blocks/(double)info.rblocks : 0);
	logg("Time: %u.%3.3u sec (%u m %u s)\n", ds, dms/1000, ds/60, ds%60);
    }

    optfree(opts);

#if defined(C_WINDOWS) && defined(CL_THREAD_SAFE)
    if(!pthread_win32_process_detach_np()) {
	logg("!Can't stop the win32 pthreads layer\n");
	return 72;
    }
#endif

    return ret;
}