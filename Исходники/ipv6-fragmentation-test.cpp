void
Ipv6FragmentationTest::HandleReadServer (Ptr<Socket> socket)
{
  Ptr<Packet> packet;
  Address from;
  while ((packet = socket->RecvFrom (from)))
    {
      if (Inet6SocketAddress::IsMatchingType (from))
        {
          packet->RemoveAllPacketTags ();
          packet->RemoveAllByteTags ();

          m_receivedPacketServer = packet->Copy ();
        }
    }
}