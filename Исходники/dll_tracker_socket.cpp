 SOCKET __stdcall track_accept(SOCKET s, struct sockaddr FAR * addr, OUT int FAR * addrlen)
 {
   uintptr_t loc = (uintptr_t)_ReturnAddress();
   
   SOCKET socket = dllaccept(s, addr, addrlen);
   if (socket>=0) 
     tracker_socket_track(loc, socket);
   return socket;
 }