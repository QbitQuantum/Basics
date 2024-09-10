    // -------------------------------------------------
    // events
    void TcpServerSocketEmul::OnNewConnection(Utils::SafeRef<ITcpSocketEmul> pClient)
    {
        boost::shared_ptr<TcpSocketEmul> pServer(new TcpSocketEmul(m_thread));
        TUT_ASSERT(pServer.get() != 0);
        pServer->setOther(pClient);
        pClient->setOther(pServer.get());
        pServer->ConnectToHost(pClient->LocalHostInf()); 
        pClient->Connected();
        // pServer->Connected();

        m_pOwner->NewConnection(pServer);
    }