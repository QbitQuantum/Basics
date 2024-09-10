/** @return false and set error code and description string on failure  */
bool ArSocket::connect(const char *host, int port, Type type,
		       const char *openOnIP)
{
  char localhost[maxHostNameLen()];
  myError=NoErr;
  myErrorStr.clear();
  if (!host)
  {
    if (gethostname(localhost, sizeof(localhost)) == 1)
    {
      myError=ConBadHost;
      myErrorStr="Failure to locate host '";
      myErrorStr+=localhost;
      myErrorStr+="'";
      ArLog::logErrorFromOS(ArLog::Normal, "ArSocket::connect: gethostname failed");
      return(false);
    }
    host=localhost;
  }

  bzero(&mySin, sizeof(mySin));
  // MPL taking out this next code line from the if since it makes
  // everything we can't resolve try to connect to localhost
  // &&  !hostAddr("localhost", mySin.sin_addr))

  char useHost[1024];
  int usePort;
  separateHost(host, port, useHost, sizeof(useHost), &usePort);

  if (!hostAddr(useHost, mySin.sin_addr))
    return(false);
  setRawIPString();
  mySin.sin_family=AF_INET;
  mySin.sin_port=hostToNetOrder(usePort);

  if ((type == TCP) && ((myFD=socket(AF_INET, SOCK_STREAM, 0)) < 0))
  {
    myError=NetFail;
    myErrorStr="Failure to make TCP socket";
    ArLog::logErrorFromOS(ArLog::Normal, "ArSocket::connect: could not make tcp socket");
    return(false);
  }
  else if ((type == UDP) && ((myFD=socket(AF_INET, SOCK_DGRAM, 0)) < 0))
  {
    myError=NetFail;
    myErrorStr="Failure to make UDP socket";
    ArLog::logErrorFromOS(ArLog::Normal, "ArSocket::connect: could not make udp socket");
    return(false);
  }

  ArUtil::setFileCloseOnExec(myFD);

  if (openOnIP != NULL)
  {
    struct sockaddr_in outSin;
    if (!hostAddr(openOnIP, outSin.sin_addr))
    {
      myError = NameLookup;
      myErrorStr = "Name lookup failed";
      ArLog::log(ArLog::Normal, "Couldn't find ip of %s to open on", openOnIP);
      return(false); 
    }
    outSin.sin_family=AF_INET;
    outSin.sin_port=hostToNetOrder(0);
    if (bind(myFD, (struct sockaddr *)&outSin, sizeof(outSin)) < 0)
    {
      ArLog::logErrorFromOS(ArLog::Normal, "ArSocket::connect: Failure to bind socket to port %d", 0);
      return(false);
    }
  }

  myType=type;

  if (::connect(myFD, (struct sockaddr *)&mySin,
		sizeof(struct sockaddr_in)) < 0)
  {
    myErrorStr="Failure to connect socket";
    switch (errno)
    {
    case ECONNREFUSED:
      myError=ConRefused;
      myErrorStr+="; Connection refused";
      break;
    case ENETUNREACH:
      myError=ConNoRoute;
      myErrorStr+="; No route to host";
      break;
    default:
      myError=NetFail;
      break;
    }
    ArLog::logErrorFromOS(ArLog::Verbose, "ArSocket::connect: could not connect");

    ::close(myFD);
    myFD = -1;
    return(false);
  }

  return(true);
}