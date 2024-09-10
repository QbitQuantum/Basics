void TestSSLServer::serve() {
  TSocketAddress addr;
  socket_->getAddress(&addr);
  getEventHandler()->preServe(&addr);

  while (!stopped_) {
    std::shared_ptr<TRpcTransport> sock = socket_->accept();
    TSSLSocket *sslSock = dynamic_cast<TSSLSocket*>(sock.get());
    BOOST_CHECK(sslSock);

    // read()
    uint8_t buf[128];
    uint32_t bytesRead = sslSock->readAll(buf, sizeof(buf));
    BOOST_CHECK_EQUAL(bytesRead, 128);

    // write()
    sslSock->write(buf, sizeof(buf));
  }

  cerr << "TestSSLServer::serve() terminates" << endl;
}