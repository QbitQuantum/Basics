  void TCPCONNECTIONTF::testClose()
  {
    TCPServerAdapter adapter;
    Transport *tranServer = new Transport;
    char spec[] = "tcp:localhost:13345";

    tranServer->start();
    IOComponent *listener = tranServer->listen(spec, _streamer, &adapter);
    CPPUNIT_ASSERT(listener);

    
    //start client
    Transport *tranClient = new Transport;
    tranClient->start();
    Connection *conn = tranClient->connect(spec, _streamer, false);
    CPPUNIT_ASSERT(conn);
    CPPUNIT_ASSERT(_conn->postPacket(new ConnPacket(31), _handler, NULL));
    
    // the close() has not implement
    ANET_LOG(SPAM,"Before Calling _conn->close();");
    _conn->close();
    ANET_LOG(SPAM,"After Calling _conn->close();");
    CPPUNIT_ASSERT(_conn->isClosed());
    ANET_LOG(SPAM,"After Assert(_conn->isClosed();");
    tranClient->stop();
    ANET_LOG(SPAM,"After Calling tranClient->stop();");
    tranClient->wait();
    ANET_LOG(SPAM,"After Calling tranClient->wait();");
    tranServer->stop();
    ANET_LOG(SPAM,"After Calling tran_server->stop();");
    tranServer->wait();
    ANET_LOG(SPAM,"After Calling tranClient->wait();");
    delete tranClient;
    delete tranServer;
    listener->subRef();
    conn->subRef();
  }