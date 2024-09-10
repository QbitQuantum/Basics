void Ping6::HandleRead (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);

  Ptr<Packet> packet=0;
  Address from;
  while ((packet = socket->RecvFrom (from)))
    {
      if (Inet6SocketAddress::IsMatchingType (from))
        {
          Ipv6Header hdr;
          Icmpv6Echo reply (0);
          Inet6SocketAddress address = Inet6SocketAddress::ConvertFrom (from);

          packet->RemoveHeader (hdr);

          uint8_t type;
          packet->CopyData (&type, sizeof(type));

          switch (type)
            {
            case Icmpv6Header::ICMPV6_ECHO_REPLY:
              packet->RemoveHeader (reply);

              NS_LOG_INFO ("Received Echo Reply size  = " << std::dec << packet->GetSize () << " bytes from " << address.GetIpv6 () << " id =  " << (uint16_t)reply.GetId () << " seq = " << (uint16_t)reply.GetSeq ());
              break;
            default:
              /* other type, discard */
              break;
            }
        }
    }
}