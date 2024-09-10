int ServerThread::InitServer(int max_connections)
// Initialize the server. Returns a non-zero value if any
// errors ocurr.
{
  if(InitSocketLibrary() == 0) {
    if(InitSocket(SOCK_STREAM, servercfg->port) < 0) return 1;
  }
  else {
    return 1;
  }

  int val = 1;
  if(SetSockOpt(gxsocket, SOL_SOCKET, SO_REUSEADDR,
		&val, sizeof(val)) < 0) {
    CheckSocketError((gxSocket *)this, "Error initializing server"); 
    Close();
    return 1;
  }

  // Bind the name to the socket
  if(Bind() < 0) {
    CheckSocketError((gxSocket *)this, "Error initializing server"); 
    Close();
    return 1;
  }
  
  // Listen for connections with a specified backlog
  if(Listen(max_connections) < 0) {
    CheckSocketError((gxSocket *)this, "Error initializing server");
    Close();
    return 1;
  }

  return 0;
}