void 
DynamicGlobalRoutingTestCase::HandleRead (Ptr<Socket> socket)
{
  Ptr<Packet> packet;
  Address from;
  while ((packet = socket->RecvFrom (from)))
    {
      if (packet->GetSize () == 0)
        { //EOF
          break;
        }
      Ipv4PacketInfoTag tag;
      bool found;
      found = packet->PeekPacketTag (tag);
      uint8_t now = static_cast<uint8_t> (Simulator::Now ().GetSeconds ());
      if (found)
        {
          if (tag.GetRecvIf () == 1)
            {
              m_firstInterface[now]++;
            }
          if (tag.GetRecvIf () == 2)
            {
              m_secondInterface[now]++;
            }
          m_count++;
        }
    }
}