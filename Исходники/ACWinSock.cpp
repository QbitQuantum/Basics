/**
 * Create socketobjects as server and make them ready for traffic.
 * The server just needs to listen to the port the client is sending
 * its data to.
 */
HRESULT ACWinSock::CreateServer(ACSocketObject **ppSkObject) 
{
   UINT nEvents=0;

	//Log("firing up server");
	(*ppSkObject) = new ACSocketObject(mpLOG);
   
	if (!(*ppSkObject)) 
	{
		Log("[ERROR]  m_pSkObject construction failed in ACWinSock::CreateServer");
		return AC_FAIL;
	}
	Log("ACSocketObjects constructed");

	// 1. step: create a socket object
	if (FAILED( (*ppSkObject)->CreateSocket() ))
		return AC_FAIL;
	Log("socket created");
   
	// 2. step: name the socket cause it's a server
	if (FAILED( (*ppSkObject)->Bind(mPort) ))
		return AC_FAIL;
	Log("server bind to port: %d", mPort);

	// 3. step: listen for incoming connection requests
	if (FAILED( (*ppSkObject)->Listen() ))
		return AC_FAIL;
	Log("server is now listening for incoming connection...");

	nEvents |= FD_READ | FD_WRITE | FD_CONNECT | FD_ACCEPT | FD_CLOSE;

	// 4. step: notification from windows WM_ about incoming events
	if (WSAAsyncSelect((*ppSkObject)->GetSocket(), mActiveWnd, WM_ACSERVER, nEvents)==SOCKET_ERROR) 
	{
		Log("[ERROR]  WSAAsyncSelect(WM_ACSERVER) failed");
		mpSockObj->Disconnect();
		return AC_FAIL;
	}

	// initialize all client slots as invalid
	for (int i=0; i<256; i++) 
	{
		mClients[i].skToClient = INVALID_SOCKET;
		mClients[i].nID = 0;
	}

	return AC_OK;
};