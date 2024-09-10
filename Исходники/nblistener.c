int nbListenerReader(void *session){
  NB_Listener *sel=(NB_Listener *)session;

#if defined(WIN32)
  int mode=0;
  WSAResetEvent(sel->hEvent);
  WSAEventSelect((SOCKET)sel->fildes,sel->hEvent,0);
  ioctlsocket((SOCKET)sel->fildes,FIONBIO,&mode); // Make the socket blocking
#endif 
  (sel->handler)(sel->context,sel->fildes,sel->session);
#if defined(WIN32)
  WSAEventSelect((SOCKET)sel->fildes,sel->hEvent,FD_ACCEPT|FD_READ);
#endif
  return(0);
  }