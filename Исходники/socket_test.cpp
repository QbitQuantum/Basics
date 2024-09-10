TEST(SocketTest, set_recv_timeout) {
  Socket *sock = Socket::udp();
  sock->set_recv_timeout(1);
  char buf[1];
  int ret = sock->recv(buf, sizeof buf, 0);
  ASSERT_EQ(-2, ret);
}