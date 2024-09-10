//-------------------------------------------------------------------------------------
int UDPPacket::recvFromEndPoint(EndPoint & ep, Address* pAddr)
{
	KBE_ASSERT(maxBufferSize() > wpos());

	// 当接收来的大小大于接收缓冲区的时候，recvfrom返回-1
	int len = ep.recvfrom(data() + wpos(), size() - wpos(),
		(u_int16_t*)&pAddr->port, (u_int32_t*)&pAddr->ip);

	if(len > 0)
		wpos(wpos() + len);

	return len;
}