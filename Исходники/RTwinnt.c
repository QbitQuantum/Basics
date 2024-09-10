int DYNINSTasyncConnect(int mutatorpid)
{
  int sock_fd;
  struct sockaddr_in sadr;
  struct in_addr *inadr;
  struct hostent *hostptr;
  
  WORD wsversion = MAKEWORD(2,0);
  WSADATA wsadata;
  rtBPatch_asyncEventRecord ev;

  if (async_socket != -1) {
      return 0;
  }
  RTprintf("%s[%d]:  inside DYNINSTasyncConnect\n", __FILE__, __LINE__);
  if (0 == connect_port) {
    fprintf(stderr, "%s[%d]:  DYNINSTasyncConnect, no port\n",
            __FILE__, __LINE__);    
  }

  WSAStartup(wsversion, &wsadata);
   
  RTprintf("%s[%d]:  inside DYNINSTasyncConnect before gethostbyname\n", __FILE__, __LINE__);
  hostptr = gethostbyname("localhost");
  inadr = (struct in_addr *) ((void*) hostptr->h_addr_list[0]);
  RTprintf("%s[%d]:  inside DYNINSTasyncConnect before memset\n", __FILE__, __LINE__);
  memset((void*) &sadr, 0, sizeof(sadr));
  sadr.sin_family = PF_INET;
  sadr.sin_port = htons((u_short)connect_port);
  sadr.sin_addr = *inadr;

  RTprintf("%s[%d]:   DYNINSTasyncConnect before socket\n", __FILE__, __LINE__);
  sock_fd = socket(PF_INET, SOCK_STREAM, 0);
  if (sock_fd == INVALID_SOCKET) {
    fprintf(stderr, "DYNINST: socket failed: %d\n", WSAGetLastError());
  }

  RTprintf("%s[%d]:   DYNINSTasyncConnect before connect\n", __FILE__, __LINE__);
  if (connect(sock_fd, (struct sockaddr *) &sadr, sizeof(sadr)) == SOCKET_ERROR) {
    fprintf(stderr, "DYNINSTasyncConnect: connect failed: %d\n", WSAGetLastError());
  }

  /* maybe need to do fcntl to set nonblocking writes on this fd */

  async_socket = sock_fd;

  RTprintf("%s[%d]:   DYNINSTasyncConnect before write\n", __FILE__, __LINE__);
  /* after connecting, we need to send along our pid */
  ev.type = rtBPatch_newConnectionEvent;
  ev.pid = _getpid();
  if (!DYNINSTwriteEvent((void *) &ev, sizeof(rtBPatch_asyncEventRecord))) {
    fprintf(stderr, "%s[%d]:  DYNINSTwriteEventFailed\n", __FILE__, __LINE__);
  }
  /* initialize comms mutex */

  //InitializeCriticalSection(&comms_mutex);
  //fprintf(stderr, "%s[%d]: DYNINSTasyncConnect appears to have succeeded\n", __FILE__, __LINE__);
  RTprintf("%s[%d]:  leaving DYNINSTasyncConnect\n", __FILE__, __LINE__);
  return 1; /*true*/
}