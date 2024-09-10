/**
 * Called when a connection completes or times out.
 */
void TCPConnectorTest::OnConnectFailure(int fd, int error) {
  // The error could be one of many things, right now we just check it's non-0
  OLA_ASSERT_NE(0, error);
  OLA_ASSERT_EQ(-1, fd);
  m_ss->Terminate();
}