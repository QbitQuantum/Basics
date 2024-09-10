/*
 * Perform a test session.
 */
static void DoSession( int CtrlSock )
{
  struct sockaddr_in LocSa;
  struct stat statbuf;
  int SaLen, Vmajor, Vminor;
  char str[256], *line, *p;

  /*
   * Get the source address from the control socket.
   */
  SaLen = sizeof LocSa;
  if( getpeername( CtrlSock, (struct sockaddr *)(&LocSa), &SaLen ) != 0 ) {
    syslog( LOG_ERR, "Can't get source address from control socket (%m)" );
    close( CtrlSock );
    exit( 1 );
  }
  syslog( LOG_INFO, "Connection from %s:%d",
	  inet_ntoa( LocSa.sin_addr ), ntohs( LocSa.sin_port ) );
  SourceAddress = LocSa.sin_addr;

  /*
   * Check if DENYFILE exists and if so, refuse connection
   */
  if (stat(DENYFILE, &statbuf) == 0)
  {
    syslog( LOG_INFO, "Connection from %s:%d refused: DENYFILE (%s) exists",
      inet_ntoa( LocSa.sin_addr ), ntohs( LocSa.sin_port ), DENYFILE);
    Reply(CtrlSock, 410, "Service temporarily disabled. Please try later");
    usleep( 200000 );
    close( CtrlSock );
    exit( 1 );
  }

  /*
   * Get the HELO/INFO request from a client
   */
  if ((line = ReadLineTimeout(CtrlSock, 10)) == NULL)
  {
	close( CtrlSock );
	exit( 1 );
  }

  p = line;

  if (strncmp(p, "HELO ", 5) != 0)
  {
    if (strncmp(p, "INFO", 4) != 0)
    {
      Reply(CtrlSock, 510, "Syntax error");
      close( CtrlSock );
      exit( 1 );
    }
    else {
    /* Send INFO */
      char str[100];
      int i = 0;
      while (strlen(Info[i])) {
        sprintf(str, "250-%s\r\n", Info[i]);
        if (write(CtrlSock, str, strlen(str)) != strlen(str)) {
          syslog( LOG_ERR, "Error writing to socket (%m)");
          close( CtrlSock );
          exit( 1 );
        }
        i++;
      }
      Reply(CtrlSock, 250, "");
    }
  }
  else {
    char tBuf[50];
    memset(tBuf, 0, 50);
    p += 5;
    if (CopyTagField(tBuf, 49, p, "vmajor"))
	    Vmajor = atoi(tBuf);
    else
	    Vmajor = 0;
    if (CopyTagField(tBuf, 49, p, "vminor"))
	    Vminor = atoi(tBuf);
    else
	    Vminor = 0;


    if (Vmajor < MajorVersion)
    {
      sprintf(str, "You need to upgrade, Go to %s", UPGRADE_URL);
      Reply(CtrlSock, 501, str);
      usleep( 200000 );
      close( CtrlSock );
      exit( 1 );
    }

    SendServerList( CtrlSock );
  }

  usleep( 200000 );
  close( CtrlSock );
  exit( 0 );

}