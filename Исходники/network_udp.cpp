/* Broadcast to all ips */
static void NetworkUDPBroadCast(NetworkUDPSocketHandler *socket)
{
	for (NetworkAddress *addr = _broadcast_list.Begin(); addr != _broadcast_list.End(); addr++) {
		Packet p(PACKET_UDP_CLIENT_FIND_SERVER);

		DEBUG(net, 4, "[udp] broadcasting to %s", addr->GetHostname());

		socket->SendPacket(&p, addr, true, true);
	}
}