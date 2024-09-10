 SocketInitializer()
 {
     WSADATA init;
     WSAStartup(MAKEWORD(2, 2), &init);
 }