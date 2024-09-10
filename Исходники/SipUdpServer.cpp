UtlBoolean SipUdpServer::sendTo(const SipMessage& message,
                               const char* address,
                               int port,
                               const char* szLocalSipIp)
{
    UtlBoolean sendOk;
    UtlVoidPtr* pServerContainer = NULL;
    SipClient* pServer = NULL;
    
    if (szLocalSipIp)
    {
        UtlString localKey(szLocalSipIp);
        pServerContainer = (UtlVoidPtr*)this->mServers.findValue(&localKey);
        if (pServerContainer)
        {
            pServer = (SipClient*) pServerContainer->getValue();
        }
    }
    else
    {
        // no local sip IP specified, so, use the default one
        UtlString defaultKey(mDefaultIp);
       
        pServerContainer = (UtlVoidPtr*) mServers.findValue(&defaultKey);
        if (pServerContainer)
        {
            pServer = (SipClient*) pServerContainer->getValue();
        }
    }
    
    if (pServer)
    {
        sendOk = pServer->sendTo(message, address, port);
    }
    else
    {
        sendOk = false;
    }
    return(sendOk);
}