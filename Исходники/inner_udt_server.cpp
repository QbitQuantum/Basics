void InnerUdtServer::handle_accept(std::shared_ptr<InnerUdtConnection> conn) {
  accept();
  conn->accept();
}