int SIO_WaitForData(SIO_INFO *s,long timedelay)
{
#ifdef WINDOWS
  int ret;
  long tms;
  DWORD err;
  DWORD emask;
  COMMTIMEOUTS ct;
  COMSTAT comstat;

  /* sanity check */
  if (s==NULL)
    return -1;

  tms=timedelay/1000;
  tms+=ADD_DELAY;

  ret=0;
  GetCommTimeouts(s->fd,&ct);
  if (timedelay==SIO_READ_WAIT_FOREVER) {
    ct.ReadIntervalTimeout=MAXDWORD;
    ct.ReadTotalTimeoutMultiplier=0;
    ct.ReadTotalTimeoutConstant=MAXDWORD;
  } else {
    ct.ReadIntervalTimeout=tms;
    ct.ReadTotalTimeoutMultiplier=10;
    ct.ReadTotalTimeoutConstant=tms;
    /*
    ct.ReadIntervalTimeout=10;
    ct.ReadTotalTimeoutMultiplier=10;
    ct.ReadTotalTimeoutConstant=100;
    */
  }
  SetCommTimeouts(s->fd,&ct);

  /* have a quick look to see if there is data in the buffers
   * still ... and return notification to the caller without
   * doing any of the messy thread stuff with timeouts
   */
  ClearCommError(s->fd,&emask,&comstat);
  if (comstat.cbInQue>0)
    return(1);

#if 0
  /* now wait for a character to arrive ... unfortunately this
   * operation does not have any form of timeout on it which
   * makes it rather useless for detecting IO!
   */
  emask=EV_RXCHAR|EV_ERR|EV_RLSD|EV_CTS|EV_DSR;
  ret=WaitCommEvent(s->fd,&emask,NULL);
  if (ret) {
    /* we have a character we can read ... */
    return(1);
  } else {
    err=GetLastError();
    return(-1);
  }
#endif

  /* get the worker thread to start doing something */
  s->eventMask=EV_RXCHAR|EV_ERR|EV_RLSD|EV_CTS|EV_DSR; /* Custom: DCD? */

#ifdef NO_THREADS
  /* use overlapped I/O notification to simulate having
   * a timeout on WaitCommEvent() 
   */
  sio_init_overlapped(s);
  if (WaitCommEvent(s->fd,&s->eventMask,s->overlapped)==FALSE) {
    err=GetLastError();
    if (err==ERROR_IO_PENDING) {
  if (sio_wait_overlapped(s,timedelay)) {
    return(1);
  } else {
    return(-1);
  }
    }
  } else {
    return(1);
  }
#else /* !NO_THREADS */

  /* this thread stuff works fine under Win95 but doesn't under WinNT */
  SetEvent(s->hStartWait);
  err=WaitForSingleObject(s->hFinishedWait,tms);

  switch(err) {
    case WAIT_OBJECT_0:
      return(1);
    case WAIT_ABANDONED:
    case WAIT_TIMEOUT:
    default:
      {
        DWORD oldMask;

        /* make WaitCommEvent return in the worker thread */
        GetCommMask(s->fd,&oldMask);
        SetCommMask(s->fd,0);
        SetCommMask(s->fd,oldMask);

      }
        return(-1);
  }
#endif /* NO_THREADS */

#elif defined( __palmos__ )
  Long timeout;

  /* sanity check */
  if (s==NULL)
    return -1;

  if( timedelay==SIO_READ_WAIT_FOREVER ) {
    timeout = -1;
  } else {
    timeout = ( ( timedelay * sysTicksPerSecond ) / 1000000 ) + 1;
  }

  if( SerReceiveWait( s->fd, 1, (Long) timeout )!=0 ) return( -1 );

  return( 1 );

#else /* !WINDOWS && !__palmos__ */
  int ret;
  fd_set readfds;
  struct timeval tv, *tvwait;

  /* sanity check */
  if (s==NULL)
    return -1;

  /* isn't the Unix way of doing this so much more elegant :-) */
  FD_ZERO(&readfds); 
  FD_SET(s->fd,&readfds);

  tv.tv_sec=0; 
  tv.tv_usec=timedelay;

  if (timedelay==SIO_READ_WAIT_FOREVER)
    tvwait=NULL;
  else
    tvwait=&tv;

  ret=select(s->fd+1,&readfds,NULL,NULL,tvwait);

  /* if there is one descriptor ready for read then it is
   * a success ... so we can just use the return from select
   */
  return(ret);
#endif /* WINDOWS */

}