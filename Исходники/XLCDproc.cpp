bool XLCDproc::Connect()
{
  CloseSocket();

  struct hostent *server;
  server = gethostbyname(g_advancedSettings.m_lcdHostName);
  if (server == NULL)
  {
     CLog::Log(LOGERROR, "XLCDproc::%s - Unable to resolve LCDd host.", __FUNCTION__);
     return false;
  }

  m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (m_sockfd == -1)
  {
    CLog::Log(LOGERROR, "XLCDproc::%s - Unable to create socket.", __FUNCTION__);
    return false;
  }

  struct sockaddr_in serv_addr = {};
  serv_addr.sin_family = AF_INET;
  memmove(&serv_addr.sin_addr, server->h_addr_list[0], server->h_length);
  //Connect to default LCDd port, hard coded for now.
  serv_addr.sin_port = htons(13666);

  if (connect(m_sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
  {
    CLog::Log(LOGERROR, "XLCDproc::%s - Unable to connect to host, LCDd not running?", __FUNCTION__);
    return false;
  }

  // Start a new session
  CStdString hello;
  hello = "hello\n";

  if (write(m_sockfd,hello.c_str(),hello.size()) == -1)
  {
    CLog::Log(LOGERROR, "XLCDproc::%s - Unable to write to socket", __FUNCTION__);
    return false;
  }

  // Receive LCDproc data to determine row and column information
  char reply[1024];
  if (read(m_sockfd,reply,1024) == -1)
  {
    CLog::Log(LOGERROR, "XLCDproc::%s - Unable to read from socket", __FUNCTION__);
    return false;
  }

  unsigned int i=0;
  while ((strncmp("lcd",reply + i,3) != 0 ) && (i < (strlen(reply) - 5))) i++;
  if(sscanf(reply+i,"lcd wid %u hgt %u", &m_iColumns, &m_iRows))
    CLog::Log(LOGDEBUG, "XLCDproc::%s - LCDproc data: Columns %i - Rows %i.", __FUNCTION__, m_iColumns, m_iRows);

  //Build command to setup screen
  CStdString cmd;
  cmd = "screen_add xbmc\n";
  if (!g_advancedSettings.m_lcdHeartbeat)
    cmd.append("screen_set xbmc -heartbeat off\n");
  if (g_advancedSettings.m_lcdScrolldelay != 0)
  {
    cmd.append("widget_add xbmc line1 scroller\n");
    cmd.append("widget_add xbmc line2 scroller\n");
    cmd.append("widget_add xbmc line3 scroller\n");
    cmd.append("widget_add xbmc line4 scroller\n");
  }
  else
  {
    cmd.append("widget_add xbmc line1 string\n");
    cmd.append("widget_add xbmc line2 string\n");
    cmd.append("widget_add xbmc line3 string\n");
    cmd.append("widget_add xbmc line4 string\n");
  }

  //Send to server
  if (write(m_sockfd,cmd.c_str(),cmd.size()) == -1)
  {
    CLog::Log(LOGERROR, "XLCDproc::%s - Unable to write to socket", __FUNCTION__);
    return false;
  }

  return true;
}