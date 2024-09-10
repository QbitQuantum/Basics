void end_socklib ( void )
{
#ifdef WIN_TCP
  WSACleanup();
#endif
}