bool SimpleSocket::isReadyReceive(int timeout)
{
  timeval time;
  fd_set read, write, except;
  int rc = this->SOCKET_FAIL;
  bool rtn = false;
  
  // The select function uses the timeval data structure
  time.tv_sec = timeout/1000;
  time.tv_usec = (timeout%1000)*1000;
  
  FD_ZERO(&read);
  FD_ZERO(&write);
  FD_ZERO(&except);
  
  FD_SET(this->getSockHandle(), &read);
  
  rc = SELECT(this->getSockHandle() + 1, &read, &write, &except, &time);
  
  if (this->SOCKET_FAIL != rc)
  {
    if (0==rc)
    {
      LOG_DEBUG("Socket select timed out");
      rtn = false;
    }
    else
    {
      LOG_DEBUG("Data is ready for reading");
      rtn = true;
    }
  }
  else
  {
    this->logSocketError("Socket select function failed", rc);
    rtn = false;
  }
  
  return rtn;
}