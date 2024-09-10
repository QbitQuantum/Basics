int SocketTwoWayStream::open(const Contact& address) {
    if (address.getPort()==-1) {
        return -1;
    }
    String host = address.getHost();
#ifdef YARP_HAS_ACE
    ACE_SOCK_Connector connector;
    if (address.getHost() == "localhost") {
        // ACE does not like localhost.  At all.
        NameConfig config;
        host = config.getHostName(true);
    }
    ACE_INET_Addr addr(address.getPort(),host.c_str());
    ACE_Time_Value openTimeout;
    ACE_Time_Value *timeout = NULL;
    if (address.hasTimeout()) {
        openTimeout.set(address.getTimeout());
        timeout = &openTimeout;
    }
    int result = connector.connect(stream,addr,timeout,ACE_Addr::sap_any,1);
#else
    TcpConnector connector;
    int result = connector.connect(stream, address);
#endif
    if (result>=0) {
        happy = true;
    } else {
        YARP_SPRINTF2(Logger::get(),
                      debug,
                      "TCP connection to tcp://%s:%d failed to open",
                      host.c_str(),
                      address.getPort());
    }
    updateAddresses();
    return result;
}