/*
 * Called when a connection completes or times out.
 */
void AdvancedTCPConnectorTest::OnConnect(TcpSocket *socket) {
  CPPUNIT_ASSERT(socket);

  IPV4Address address;
  uint16_t port;
  CPPUNIT_ASSERT(socket->GetPeer(&address, &port));
  CPPUNIT_ASSERT_EQUAL(m_localhost, address);

  m_connected_socket = socket;
  m_ss->Terminate();
}