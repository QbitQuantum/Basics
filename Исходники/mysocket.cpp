int MySocket::GetIPAddress(char *sbuf)
// Pass back the IP Address of this machine in the "sbuf" variable.
// A memory buffer equal to "MysMAX_NAME_LEN" must be pre-allocated
// prior to using this function. Return -1 if an error occurs.
{
  char hostname[MysMAX_NAME_LEN];
  int rv = GetHostName(hostname);
  if(rv < 0) return rv;

  in_addr *ialist;
  hostent *hostinfo = GetHostInformation(hostname);
  if(!hostinfo) {
    socket_error = MySOCKET_HOSTNAME_ERROR;
    return -1;
  }
  ialist = (in_addr *)hostinfo->h_addr_list[0];

  // Prevent crashes if memory has not been allocated
  if(!sbuf) sbuf = new char[MysMAX_NAME_LEN]; 

  strcpy(sbuf, inet_ntoa(*ialist));
  delete hostinfo;
  return 0;
}