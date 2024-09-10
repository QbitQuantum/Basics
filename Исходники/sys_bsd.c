void
sys_telnet_init (void)
{
  (void) signal (SIGINT, intr);
  (void) signal (SIGQUIT, intr2);
  (void) signal (SIGPIPE, deadpeer);
#ifdef	SIGWINCH
  (void) signal (SIGWINCH, sendwin);
#endif
#ifdef	SIGTSTP
  (void) signal (SIGTSTP, susp);
#endif
#ifdef	SIGINFO
  (void) signal (SIGINFO, ayt);
#endif

  setconnmode (0);

  NetNonblockingIO (net, 1);

#if	defined(TN3270)
  if (noasynchnet == 0)
    {				/* DBX can't handle! */
      NetSigIO (net, 1);
      NetSetPgrp (net);
    }
#endif /* defined(TN3270) */

#if	defined(SO_OOBINLINE)
  if (SetSockOpt (net, SOL_SOCKET, SO_OOBINLINE, 1) == -1)
    {
      perror ("SetSockOpt");
    }
#endif /* defined(SO_OOBINLINE) */
}