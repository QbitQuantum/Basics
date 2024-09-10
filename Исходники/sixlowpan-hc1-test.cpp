void SixlowpanHc1ImplTest::ReceivePkt (Ptr<Socket> socket)
{
  uint32_t availableData;
  availableData = socket->GetRxAvailable ();
  m_receivedPacket = socket->Recv (std::numeric_limits<uint32_t>::max (), 0);
  NS_ASSERT (availableData == m_receivedPacket->GetSize ());
  //cast availableData to void, to suppress 'availableData' set but not used
  //compiler warning
  (void) availableData;
}