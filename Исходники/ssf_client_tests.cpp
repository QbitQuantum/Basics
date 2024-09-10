void InitTCPServer(boost::asio::ip::tcp::acceptor& server, int server_port) {
  boost::system::error_code server_ec;
  boost::asio::ip::tcp::endpoint server_ep(boost::asio::ip::tcp::v4(),
                                           server_port);
  server.open(boost::asio::ip::tcp::v4(), server_ec);
  ASSERT_EQ(0, server_ec.value()) << "Could not open server acceptor";
  server.bind(server_ep, server_ec);
  ASSERT_EQ(0, server_ec.value()) << "Could not bind server acceptor";
  server.listen(boost::asio::socket_base::max_connections, server_ec);
  ASSERT_EQ(0, server_ec.value()) << "Server acceptor could not listen";
}