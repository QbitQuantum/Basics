//-------------------------------------------------------------------------------------
int TCPPacket::recvFromEndPoint(EndPoint & ep, Address* pAddr)
{
	//KBE_ASSERT(MessageHandlers::pMainMessageHandlers != NULL && "Must set up a MainMessageHandlers!\n");
	KBE_ASSERT(maxBufferSize() > wpos());
	int len = ep.recv(data() + wpos(), (int)(size() - wpos()));
	
	if(len > 0) 
	{
		wpos((int)(wpos() + len));

		// 注意:必须在大于0的时候否则DEBUG_MSG将会导致WSAGetLastError返回0从而陷入死循环
		// DEBUG_MSG(fmt::format("TCPPacket::recvFromEndPoint: datasize={}, wpos={}.\n", len, wpos()));
	}

	return len; 
}