//
// Create a socket and invoke AcceptEx.  Only the original call to to this
// function needs to be added to the IOCP.
//
// If the expected behaviour of connecting client applications is to NOT
// send data right away, then only posting one AcceptEx can cause connection
// attempts to be refused if a client connects without sending some initial
// data (notice that the associated iocpclient does not operate this way 
// but instead makes a connection and starts sending data write away).  
// This is because the IOCP packet does not get delivered without the initial
// data (as implemented in this sample) thus preventing the worker thread 
// from posting another AcceptEx and eventually the backlog value set in 
// listen() will be exceeded if clients continue to try to connect.
//
// One technique to address this situation is to simply cause AcceptEx
// to return right away upon accepting a connection without returning any
// data.  This can be done by setting dwReceiveDataLength=0 when calling AcceptEx.
//
// Another technique to address this situation is to post multiple calls 
// to AcceptEx.  Posting multiple calls to AcceptEx is similar in concept to 
// increasing the backlog value in listen(), though posting AcceptEx is 
// dynamic (i.e. during the course of running your application you can adjust 
// the number of AcceptEx calls you post).  It is important however to keep
// your backlog value in listen() high in your server to ensure that the 
// stack can accept connections even if your application does not get enough 
// CPU cycles to repost another AcceptEx under stress conditions.
// 
// This sample implements neither of these techniques and is therefore
// susceptible to the behaviour described above.
//
BOOL CreateAcceptSocket(BOOL fUpdateIOCP) {

	int nRet = 0;
	DWORD dwRecvNumBytes = 0;
	DWORD bytes = 0;

	//
	// GUID to Microsoft specific extensions
	//
	GUID acceptex_guid = WSAID_ACCEPTEX;

    //
	//The context for listening socket uses the SockAccept member to store the
	//socket for client connection. 
	//
	if( fUpdateIOCP ) {
		g_pCtxtListenSocket = UpdateCompletionPort(g_sdListen, ClientIoAccept, FALSE);
		if( g_pCtxtListenSocket == NULL ) {
			myprintf("failed to update listen socket to IOCP\n");
			return(FALSE);
		}

        // Load the AcceptEx extension function from the provider for this socket
        nRet = WSAIoctl(
            g_sdListen,
            SIO_GET_EXTENSION_FUNCTION_POINTER,
           &acceptex_guid,
            sizeof(acceptex_guid),
           &g_pCtxtListenSocket->fnAcceptEx,
            sizeof(g_pCtxtListenSocket->fnAcceptEx),
           &bytes,
            NULL,
            NULL
            );
        if (nRet == SOCKET_ERROR)
        {
            myprintf("failed to load AcceptEx: %d\n", WSAGetLastError());
            return (FALSE);
        }
	}

	g_pCtxtListenSocket->pIOContext->SocketAccept = CreateSocket();
	if( g_pCtxtListenSocket->pIOContext->SocketAccept == INVALID_SOCKET) {
		myprintf("failed to create new accept socket\n");
		return(FALSE);
	}

	//
	// pay close attention to these parameters and buffer lengths
	//
	nRet = g_pCtxtListenSocket->fnAcceptEx(g_sdListen, g_pCtxtListenSocket->pIOContext->SocketAccept,
                    (LPVOID)(g_pCtxtListenSocket->pIOContext->Buffer),
                    MAX_BUFF_SIZE - (2 * (sizeof(SOCKADDR_STORAGE) + 16)),
                    sizeof(SOCKADDR_STORAGE) + 16, sizeof(SOCKADDR_STORAGE) + 16,
                    &dwRecvNumBytes, 
					(LPOVERLAPPED) &(g_pCtxtListenSocket->pIOContext->Overlapped));
	if( nRet == SOCKET_ERROR && (ERROR_IO_PENDING != WSAGetLastError()) ) {
		myprintf("AcceptEx() failed: %d\n", WSAGetLastError());
		return(FALSE);
	}

	return(TRUE);
}