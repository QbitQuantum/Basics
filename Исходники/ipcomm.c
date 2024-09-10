/** Return the current status of DCD on this line
 *  TCP/IP Interpretation: If carrier has not been set true yet,
 *  try and accept. If that succeeds, raise carrier. This is 
 *  analogous to a modem auto-answering and raising the DCD
 *  signal on the serial port.
 *
 *  @note	This routine gets polled while Maximus is idle.
 *		This is how we recognize that a caller is online.
 *
 *  @warning	We pull a super-sneaky trick here to avoid the
 *		(normal) requirement of a listen->accept->fork
 *		daemon. We assume that max -w is being run in
 *		respawn mode (e.g. from inittab). When a call 
 *		comes in we fork and exit the parent, letting the
 *		child continue along its merry way. Respawing
 *		kicks up a new parent, and by then this process
 *		isn't listening for inbound connections anymore.
 *		This also makes it necessary for us to be running
 *		in max -n0 mode, so that each max instance has
 *		a unique node (task) number.
 * 
 *  @param	hc 	Communications handle
 *  @returns		0 when we're offline
 */
USHORT COMMAPI IpComIsOnline(HCOMM hc)
{
  fd_set 		rfds, wfds;
  struct timeval 	tv;
  DCB			dcb;

  if (!hc)
    return 0;

  if (hc->fDCD)
  {
    static byte tries = 0;
    int		rready;

    tries++; tries %= 15;
    if (tries != 0)
      goto skipCheck;	/* Only check once in a while */

    /* "Carrier"? Let's make sure the socket is okay. */
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    FD_SET(unixfd(hc), &rfds);
    FD_SET(unixfd(hc), &wfds);

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    if (((rready = select(unixfd(hc) + 1, &rfds, NULL, NULL, &tv)) < 0) || (select(unixfd(hc) + 1, NULL, &wfds, NULL, &tv) < 0))
    {
      hc->fDCD = FALSE;
      shutdown(unixfd(hc), 2);
      close(unixfd(hc));      
      unlink(lockpath);
    }

    if ((rready == 1) && hc->fDCD && (hc->peekHack == -1))
    {
      unsigned char 	buf[1];
      ssize_t		i;

      i = read(unixfd(hc), &buf, 1);
      switch(i)
      {
	case 0:
	case -1:
	  hc->fDCD = FALSE;
	  shutdown(unixfd(hc), 20);
	  close(unixfd(hc));
	  break;
	case 1:
	  hc->peekHack = buf[0];
	  break;
      }

      if (hc->fDCD == FALSE)
      {
	logit("!Caller closed TCP/IP connection (Dropped Carrier)");
      }	
    }

    skipCheck:
    return hc->fDCD ? 1 : 0;
  }

  if(hc->listenfd == -1)
    return 0;

  /* No "Carrier"? See if we can accept a connection */
  FD_ZERO(&rfds);
  FD_SET(hc->listenfd, &rfds);

  /* Will longish delay cause problems with console? */
  tv.tv_sec = 0;
  tv.tv_usec = 500000;

  if (select(hc->listenfd + 1, &rfds, NULL, NULL, &tv) > 0)
  {
    int addrSize = sizeof(*hc->saddr_p);
    int fd = -1;

    fd = accept(hc->listenfd, (struct sockaddr *)&hc->saddr_p, &addrSize);
    if (fd >= 0)
    {	
      FILE* 	f = NULL;

      /* Have accepted a socket. Close the bound socket and dump
       * the parent, so that we init can swing open a new task.
       * This technique probably won't cause us much grief, except
       * maybe on a very busy system.
       */
      /* Set accepted descriptor and other misc com parameters */
      
      f = fopen(lockpath, "w");
      fclose(f);
      
      CommHandle_setFileHandle(hc->h, fd);
      hc->fDCD = TRUE;
      hc->listenfd = -1;
      memset(&dcb, 0, sizeof(dcb));
      dcb.isTerminal = FALSE;

      dcb.fBinary	= TRUE;

      SetCommState(ComGetHandle(hc), &dcb);
      ComSetBaudRate(hc, 38400, NOPARITY, 8, ONESTOPBIT);
      _SetTimeoutBlock(hc);

      hc->burstMode = TRUE; 
      hc->burstModePending = FALSE; /* turn off nagle by default */
 
      /* Stuff a fake LF into the input stream to try and kick max 
       * into waking up faster.
       */
      hc->peekHack = '\n';

    }
  }

  return hc->fDCD ? 1 : 0;
}