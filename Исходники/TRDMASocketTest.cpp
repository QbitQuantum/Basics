void TestRDMAServer::serve() {
  folly::SocketAddress addr;
  socket_->getAddress(&addr);
  getEventHandler()->preServe(&addr);

  while (!stopped_) {
    std::shared_ptr<TRpcTransport> sock = socket_->accept();
    TRDMASocket *rdmaSock = dynamic_cast<TRDMASocket*>(sock.get());
    CHECK_NOTNULL(rdmaSock);

    // read()
    uint8_t buf[128];
    uint32_t bytesRead = rdmaSock->readAll(buf, sizeof(buf));
    ASSERT_EQ(bytesRead, 128);

    // write()
    rdmaSock->write(buf, sizeof(buf));
  }

  cerr << "TestRDMAServer::serve() terminates" << endl;
}