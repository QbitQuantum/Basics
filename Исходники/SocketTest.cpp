/*
 * Receive some data and terminate
 */
void SocketTest::ReceiveAndTerminate(ConnectedDescriptor *socket) {
  Receive(socket);
  m_ss->Terminate();
}