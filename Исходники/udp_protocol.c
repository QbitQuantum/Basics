int net_cleanup(void) 
{
#if defined(__WIN32__) || defined(WIN32)

  if ( WSACleanup() == SOCKET_ERROR ) 
    {
      if ( WSAGetLastError() == WSAEINPROGRESS ) 
	{
	  WSACancelBlockingCall();
	  WSACleanup();
	  return 0;
	}
    }
  return 0;
#else
  return 0;
#endif
}