TEST_F(SSLClientTest, client)
{
  // Create the socket based on the 'use_ssl' flag. We use this to
  // test whether a regular socket could connect to an SSL server
  // socket.
  const Try<Socket> create = Socket::create(
      flags.use_ssl ? SocketImpl::Kind::SSL : SocketImpl::Kind::POLL);
  ASSERT_SOME(create);

  Socket socket = create.get();

  Try<net::IP> ip = net::IP::parse(flags.server, AF_INET);
  EXPECT_SOME(ip);

  // Connect to the server socket located at `ip:port`.
  const Future<Nothing> connect =
    socket.connect(Address(ip.get(), flags.port));

  // Verify that the client views the connection as established.
  AWAIT_EXPECT_READY(connect);

  // Send 'data' from the client to the server.
  AWAIT_EXPECT_READY(socket.send(flags.data));

  // Verify the client received the message back from the server.
  AWAIT_EXPECT_EQ(flags.data, socket.recv());
}