void SockNonBlock(int Socket)
{
#if defined(WIN32)

    unsigned long onoff=1;

    if (ioctlsocket(Socket, FIONBIO, &onoff)==SOCKET_ERROR)
        perror("ioctlsocket() fallita.");

#elif defined(SOCKETLIB)
    int onoff=1;

    s_ioctl(Socket, FIONBIO, (char *)&onoff);
    s_ioctl(Socket, FIOASYNC, (char *)&onoff);

#elif defined(BSDSOCKETLIB)
    int onoff=1;

    IoctlSocket(Socket, FIONBIO, (char *)&onoff);
    IoctlSocket(Socket, FIOASYNC, (char *)&onoff);

#elif defined(LSCO)

  int nFlags;
  
  nFlags = fcntl( Socket, F_GETFL );
  nFlags |= O_NONBLOCK;
  if( fcntl( Socket, F_SETFL, nFlags ) < 0 )
  {
    perror( "Fatal error executing nonblock" );
    exit( 1 );
  }
#elif defined(AROS)

#else

  if (fcntl(Socket, F_SETFL, FNDELAY) == -1)    {
    perror("Noblock");
    exit (1);
  }

#endif
 
}