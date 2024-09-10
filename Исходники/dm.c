void
WaitForChild (void)
{
    pid_t		pid;
    struct display	*d;
    waitType	status;
#if !defined(X_NOT_POSIX) && !defined(__UNIXOS2__)
    sigset_t mask, omask;
#else
    int		omask;
#endif

#ifdef UNRELIABLE_SIGNALS
    /* XXX classic System V signal race condition here with RescanNotify */
    if ((pid = wait (&status)) != -1)
#else
# ifndef X_NOT_POSIX
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigaddset(&mask, SIGHUP);
    sigprocmask(SIG_BLOCK, &mask, &omask);
    Debug ("signals blocked\n");
# else
    omask = sigblock (sigmask (SIGCHLD) | sigmask (SIGHUP));
    Debug ("signals blocked, mask was 0x%x\n", omask);
# endif
    if (!ChildReady && !Rescan)
# ifndef X_NOT_POSIX
	sigsuspend(&omask);
# else
	sigpause (omask);
# endif
    ChildReady = 0;
# ifndef X_NOT_POSIX
    sigprocmask(SIG_SETMASK, &omask, (sigset_t *)NULL);
# else
    sigsetmask (omask);
# endif
    while ((pid = waitpid (-1, &status, WNOHANG)) > 0)
#endif
    {
	Debug ("Manager wait returns pid: %d sig %d core %d code %d\n",
	       pid, waitSig(status), waitCore(status), waitCode(status));
	if (autoRescan)
	    RescanIfMod ();
	/* SUPPRESS 560 */
	if ((d = FindDisplayByPid (pid))) {
	    d->pid = -1;
	    switch (waitVal (status)) {
	    case UNMANAGE_DISPLAY:
		Debug ("Display exited with UNMANAGE_DISPLAY\n");
		StopDisplay (d);
		break;
	    case OBEYSESS_DISPLAY:
		d->startTries = 0;
		d->reservTries = 0;
		Debug ("Display exited with OBEYSESS_DISPLAY\n");
		if (d->displayType.lifetime != Permanent ||
		    d->status == zombie)
		    StopDisplay (d);
		else
		    RestartDisplay (d, FALSE);
		break;
	    case OPENFAILED_DISPLAY:
		Debug ("Display exited with OPENFAILED_DISPLAY, try %d of %d\n",
		       d->startTries, d->startAttempts);
		LogError ("Display %s cannot be opened\n", d->name);
		/*
		 * no display connection was ever made, tell the
		 * terminal that the open attempt failed
		 */
#ifdef XDMCP
		if (d->displayType.origin == FromXDMCP)
		    SendFailed (d, "Cannot open display");
#endif
		if (d->displayType.origin == FromXDMCP ||
		    d->status == zombie ||
		    ++d->startTries >= d->startAttempts)
		{
		    LogError ("Display %s is being disabled\n", d->name);
		    StopDisplay (d);
		}
		else
		{
		    RestartDisplay (d, TRUE);
		}
		break;
	    case RESERVER_DISPLAY:
		d->startTries = 0;
		Debug ("Display exited with RESERVER_DISPLAY\n");
		if (d->displayType.origin == FromXDMCP || d->status == zombie)
		    StopDisplay(d);
		else {
		  Time_t now;
		  int crash;

		  time(&now);
		  crash = d->lastReserv &&
		    ((now - d->lastReserv) < XDM_BROKEN_INTERVAL);
		  Debug("time %lli %lli try %i of %i%s\n", 
			(long long)now, (long long)d->lastReserv,
			d->reservTries, d->reservAttempts,
			crash ? " crash" : "");

		  if (!crash)
		    d->reservTries = 0;

		  if (crash && ++d->reservTries >= d->reservAttempts) {
		    const char *msg =
			"Server crash frequency too high: stopping display";
		    Debug("%s %s\n", msg, d->name);
		    LogError("%s %s\n", msg, d->name);
#if !defined(HAVE_ARC4RANDOM) && !defined(DEV_RANDOM)
		    AddTimerEntropy();
#endif
		    /* For a local X server either:
		     * 1. The server exit was returned by waitpid().  So
		     *    serverPid==-1 => StopDisplay() calls RemoveDisplay()
		     *
		     * 2. The server is in zombie state or still running.  So
		     *    serverPid>1 => StopDisplay()
		     *                   a. sets status=zombie,
		     *                   b. kills the server.
		     *    The next waitpid() returns this zombie server pid
		     *    and the 'case zombie:' below then calls
		     *    RemoveDisplay().
		     */
		    StopDisplay(d);
		  } else {
		    RestartDisplay(d, TRUE);
		  }
		  d->lastReserv = now;
		}
		break;
	    case waitCompose (SIGTERM,0,0):
		Debug ("Display exited on SIGTERM, try %d of %d\n",
			d->startTries, d->startAttempts);
		if (d->displayType.origin == FromXDMCP ||
		    d->status == zombie ||
		    ++d->startTries >= d->startAttempts)
		{
		    /*
		     * During normal xdm shutdown, killed local X servers
		     * can be zombies; this is not an error.
		     */
		    if (d->status == zombie &&
			(d->startTries < d->startAttempts))
			LogInfo ("display %s is being disabled\n", d->name);
		    else
			LogError ("display %s is being disabled\n", d->name);
		    StopDisplay(d);
		} else
		    RestartDisplay (d, TRUE);
		break;
	    case REMANAGE_DISPLAY:
		d->startTries = 0;
		Debug ("Display exited with REMANAGE_DISPLAY\n");
		/*
		 * XDMCP will restart the session if the display
		 * requests it
		 */
		if (d->displayType.origin == FromXDMCP || d->status == zombie)
		    StopDisplay(d);
		else
		    RestartDisplay (d, FALSE);
		break;
	    default:
		Debug ("Display exited with unknown status %d\n", waitVal(status));
		LogError ("Unknown session exit code %d from process %d\n",
			  waitVal (status), pid);
		StopDisplay (d);
		break;
	    }
	}
	/* SUPPRESS 560 */
	else if ((d = FindDisplayByServerPid (pid)))
	{
	    d->serverPid = -1;
	    switch (d->status)
	    {
	    case zombie:
		Debug ("Zombie server reaped, removing display %s\n", d->name);
		RemoveDisplay (d);
		break;
	    case phoenix:
		Debug ("Phoenix server arises, restarting display %s\n", d->name);
		d->status = notRunning;
		break;
	    case running:
		Debug ("Server for display %s terminated unexpectedly, status %d %d\n", d->name, waitVal (status), status);
		LogError ("Server for display %s terminated unexpectedly: %d\n", d->name, waitVal (status));
		if (d->pid != -1)
		{
		    Debug ("Terminating session pid %d\n", d->pid);
		    TerminateProcess (d->pid, SIGTERM);
		}
		break;
	    case notRunning:
		Debug ("Server exited for notRunning session on display %s\n", d->name);
		break;
	    }
	}
	else
	{
	    Debug ("Unknown child termination, status %d\n", waitVal (status));
	}
    }
    StartDisplays ();
}