void UDPTransportTest::Stop() {
  if (m_ss)
    m_ss->Terminate();
}