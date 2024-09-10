// This test verifies that if an EOF arrives on a socket when there is a
// pending `recv()` call, the EOF will be correctly received.
TEST_P(NetSocketTest, EOFAfterRecv)
{
  Try<Socket> client = Socket::create();
  ASSERT_SOME(client);

  const string data = "Lorem ipsum dolor sit amet";

  Try<Socket> server = Socket::create();
  ASSERT_SOME(server);

  Try<Address> server_address = server->bind(inet4::Address::ANY_ANY());
  ASSERT_SOME(server_address);

  ASSERT_SOME(server->listen(1));
  Future<Socket> server_accept = server->accept();

  // Connect to the IP from the libprocess library, but use the port
  // from the `bind` call above. The libprocess IP will always report
  // a locally bindable IP, meaning it will also work for the server
  // socket above.
  //
  // NOTE: We do not use the server socket's address directly because
  // this contains a `0.0.0.0` IP. According to RFC1122, this is an
  // invalid address, except when used to resolve a host's address
  // for the first time.
  // See: https://tools.ietf.org/html/rfc1122#section-3.2.1.3
  AWAIT_READY(
      client->connect(Address(process::address().ip, server_address->port)));

  AWAIT_READY(server_accept);

  Socket server_socket = server_accept.get();

  AWAIT_READY(server_socket.send(data));
  AWAIT_EXPECT_EQ(data, client->recv(data.size()));

  // Make the final `recv()` call before the socket is shutdown.
  Future<string> receive = client->recv();

  server_socket.shutdown(Socket::Shutdown::READ_WRITE);

  AWAIT_EXPECT_EQ(string(), receive);
}