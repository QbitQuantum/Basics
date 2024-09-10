/**
 * Called when the descriptor is closed.
 */
void TCPTransportTest::Stop() {
  if (m_ss.get())
    m_ss->Terminate();
}