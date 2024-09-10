void FSocket::ConstructL(const StringBuffer& peer, int32_t port) 
{
    //LOG.debug("FSocket::ConstructL");
    
    StringBuffer  errorMsg;
    RHostResolver resolver; 
    RBuf          serverName;
    TNameEntry    hostAddress;
    TInetAddr     address;
    TInt          res = KErrNone;

    serverName.Assign(stringBufferToNewBuf(peer));
    
    //
    // Get the connection manager instance
    //
    FConnection* connection = FConnection::getInstance();
    if (!connection) {
        iStatus = -1;
        errorMsg = "Error opening connection";
        goto error;
    }
    // Session is owned by FConnection!
    RSocketServ* session = connection->getSession();

    //
    // Open the Client Socket tcp/ip
    //
#ifdef __WINSCW__
    // WINSCW: simply open the socket
    res = iSocket.Open(*session, KAfInet, KSockStream, KProtocolInetTcp);
#else
    // GCCE: use the existing connection
    // If first time, connect to gprs
    if (!connection->isConnected()) {
        LOG.debug("FSocket: not connected, start new connection");
        if (connection->startConnection()) {
            iStatus = -1;
            errorMsg = "FSocket: error starting connection";
            goto error;
        }
    }
    RConnection* conn = connection->getConnection();
    
    LOG.debug("Opening socket and associate with existing connection");
    res = iSocket.Open(*session, KAfInet, KSockStream, KProtocolInetTcp, *conn);
    //LOG.debug("Socket opened (err = %d)", res);
#endif
    if (res != KErrNone) {
        iStatus = -1;
        errorMsg.sprintf("FSocket : Error opening socket. code %d", res);
        goto error;
    }
    
    
    // This works if serverName is the ip address, like "x.y.z.w"
    res = address.Input(serverName);
    
    if (res != KErrNone) {
        //
        // Try to resolve the host address. (On GCCE, use the existing RConnection)
        //
        LOG.debug("Resolve IP address...");
#ifdef __WINSCW__
        res = resolver.Open(*session, KAfInet, KProtocolInetTcp);
#else
        res = resolver.Open(*session, KAfInet, KProtocolInetTcp, *conn);
#endif
        if (res != KErrNone) {
            iStatus = -2;
            errorMsg.sprintf("FSocket: Host resolver open failed. code %d", res);
            goto error;
        }
        
        resolver.GetByName(serverName, hostAddress, iStatus);
        User::WaitForRequest(iStatus);
        resolver.Close();
        if (iStatus != KErrNone) {
            errorMsg.sprintf("FSocket: DNS lookup failed. code %d", iStatus.Int());
            goto error;
        }

        // Set the socket server address/port
        address = hostAddress().iAddr;
    }
    
    address.SetPort(port);
    
    
    // --- Connect to host ---
    LOG.debug("Socket connect...");
    iSocket.Connect(address, iStatus);
    User::WaitForRequest(iStatus);
    if (iStatus != KErrNone) {
        errorMsg.sprintf("FSocket: Failed to connect to Server. code %d", iStatus.Int()); 
        goto error;
    }

    serverName.Close();
    return;
    
error:
    LOG.error("%s", errorMsg.c_str());
    serverName.Close();
    return;
}