net_ssize_t net_sendto( NET_SOCKET s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen )
{
  DWORD wrotebytes;
  WSABUF datadesc = { len, ( char* )buf };
    
  if( WSASendTo( s->s, &datadesc, 1, &wrotebytes, flags, to, tolen, NULL, NULL ) == SOCKET_ERROR )
    return 0;
  return wrotebytes;
}