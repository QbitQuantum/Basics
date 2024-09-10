int SC_exec_async(const char *shell, char **cmnds, char **dirs,
		  const char *consh, char **conenv, int nc,
		  const char *lname, const char *fname,
		  int na, int show, int ignore, int lg)
   {int is, id, nd, ns, ja, st, sig;
    int nhst, reset, ioi;
    char *ldir[1];
    fspec *filter;
    conpool *cp;
    asyncstate *as;
    SC_contextdes hnd;

    as = CMAKE(asyncstate);
    SC_MEM_INIT(asyncstate, as);

    _SC_setup_async_state(as,
			  SC_get_host_length_max(NULL, TRUE, FALSE));
    as->debug = FALSE;

    if (lname != NULL)
       {as->log = io_open(lname, "a");
	SC_setbuf(as->log, NULL);}
    else
       as->log = NULL;

/* save old interrupt state */
    hnd = SC_which_signal_handler(SC_SIGIO);
    ioi = SC_set_io_interrupts(FALSE);
    SC_signal_n(SC_SIGIO, SIG_IGN, NULL, 0);

    filter = _SC_read_filter(fname);
    shell  = SC_get_shell(shell);

/* count commands */
    SC_ptr_arr_len(ns, cmnds);

/* count the directories */
    if (dirs == NULL)
       {ldir[0] = SC_getcwd();
	dirs    = ldir;
	nd      = 1;}
    else
       SC_ptr_arr_len(nd, dirs);

/* open the connection pool */
    nhst = SC_get_nhosts(PSY_Arch);
    nc   = min(nc, nhst);
    nc   = min(nc, ns);
    cp   = SC_open_connection_pool(nc, PSY_Arch, consh, conenv,
				   na, show, ignore,
				   DEFAULT_HEARTBEAT, filter);

    cp->as   = as;
    as->pool = cp;

    sig = SETJMP(cp->cpu);
    if (sig == 0)
       {cp->active = TRUE;

/* launch all commands */
	reset = TRUE;
        for (id = 0; id < nd; id++)
	    for (is = 0; is < ns; is++)
	        {if (IS_BARRIER(cmnds[is]))
		    {while (SC_wait_pool_job(cp, DEFAULT_WAIT) != 2);
		     reset = TRUE;}
		 
		 else
		    {ja = SC_launch_pool_job(cp, na, reset, shell,
					     dirs[id], cmnds[is]);
		     if (ja < 0)
		        {LONGJMP(cp->cpu, SC_EXIT_BAD);};

		     reset = FALSE;};};

/* wait for commands to complete */
	while (SC_wait_pool_job(cp, DEFAULT_WAIT) != 2);};

    cp->active = FALSE;
    as->pool   = NULL;

    st = SC_connection_pool_status(cp);

    if (lg == TRUE)
       {SC_close_connection_pool(cp, -1, TRUE);
	as->to_stdout = FALSE;}
    else
       {as->to_stdout = FALSE;
	SC_close_connection_pool(cp, sig, TRUE);};

    CFREE(as);

/* cleanup */
    _SC_free_filter(filter);

/* restore old interrupt state */
    SC_set_io_interrupts(ioi);
    SC_restore_signal_n(SC_SIGIO, hnd);

    if (sig == SC_EXIT_BAD)
       st = sig;

    return(st);}