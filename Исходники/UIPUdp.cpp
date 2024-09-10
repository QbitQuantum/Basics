// Start building up a packet to send to the remote host specific in ip and port
// Returns 1 if successful, 0 if there was a problem with the supplied IP address or port
int
UIPUDP::beginPacket(IPAddress ip, uint16_t port)
{
  UIPEthernet.tick();
  if (ip && port)
    {
      uip_ipaddr_t ripaddr;
      uip_ip_addr(&ripaddr, ip);
#ifdef UIPETHERNET_DEBUG_UDP
      Serial.print("udp beginPacket, ");
#endif
      if (_uip_udp_conn)
        {
          _uip_udp_conn->rport = htons(port);
          uip_ipaddr_copy(_uip_udp_conn->ripaddr, &ripaddr);
        }
      else
        {
          _uip_udp_conn = uip_udp_new(&ripaddr,htons(port));
          if (_uip_udp_conn)
            {
#ifdef UIPETHERNET_DEBUG_UDP
              Serial.print("new connection, ");
#endif
              _uip_udp_conn->appstate.user = &appdata;
            }
          else
            {
#ifdef UIPETHERNET_DEBUG_UDP
              Serial.println("failed to allocate new connection");
#endif
              return 0;
            }
        }
#ifdef UIPETHERNET_DEBUG_UDP
          Serial.print("rip: ");
          Serial.print(ip);
          Serial.print(", port: ");
          Serial.println(port);
#endif
    }
  if (_uip_udp_conn)
    {
      if (appdata.packet_out == NOBLOCK)
        {
          appdata.packet_out = UIPEthernet.network.allocBlock(UIP_UDP_MAXPACKETSIZE);
          appdata.out_pos = UIP_UDP_PHYH_LEN;
          if (appdata.packet_out != NOBLOCK)
            return 1;
#ifdef UIPETHERNET_DEBUG_UDP
          else
            Serial.println("failed to allocate memory for packet");
#endif
        }
#ifdef UIPETHERNET_DEBUG_UDP
      else
        Serial.println("previous packet on that connection not sent yet");
#endif
    }
  return 0;
}