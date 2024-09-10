bool C4Network2IO::Connect(const C4NetIO::addr_t &addr, C4Network2IOProtocol eProt, const C4ClientCore &nCCore, const char *szPassword) // by main thread
{
    // get network class
    C4NetIO *pNetIO = getNetIO(eProt);
    if (!pNetIO) return false;
    // already connected/connecting?
    if (GetConnectionByConnAddr(addr, pNetIO)) return true;
    // assign new connection ID, peer address isn't known yet
    uint32_t iConnID = iNextConnID++;
    C4NetIO::addr_t paddr;
    ZeroMem(&paddr, sizeof paddr);
    // create connection object and add to list
    C4Network2IOConnection *pConn = new C4Network2IOConnection();
    pConn->Set(pNetIO, eProt, paddr, addr, CS_Connect, szPassword, iConnID);
    pConn->SetCCore(nCCore);
    AddConnection(pConn);
    // connect
    if (!pConn->Connect())
    {
        // show error
        LogF("Network: could not connect to %s:%d using %s: %s", inet_ntoa(addr.sin_addr), htons(addr.sin_port),
             getNetIOName(pNetIO), pNetIO->GetError() ? pNetIO->GetError() : "");
        pNetIO->ResetError();
        // remove class
        RemoveConnection(pConn);
        return false;
    }
    // ok, wait for connection
    return true;
}