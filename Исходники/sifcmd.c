///////////////////////////////////////////////////////////////////////[10]
int SifCallRpc(struct sifcmd_RPC_CLIENT_DATA *client, unsigned int fno, unsigned int mode, void *send, int ssize, void *receive, int rsize, void (*end_func)(void*), void *end_para){
	RPC_PACKET_CALL *packet;

	if ((packet=(RPC_PACKET_CALL *)rpc_get_packet(&rpc_common))==0)
		return -1;
	client->hdr.pkt_addr=(void*)packet;
	client->func   = end_func;
	client->param  = end_para;
	client->hdr.rpc_id= packet->packet.packet.pid;

	packet->packet.packet.paddr  = packet;
	packet->packet.client = client;
	packet->packet.fno    = fno;
	packet->size   = ssize;
	packet->receive= receive;
	packet->rsize  = rsize;
	packet->server = client->server;

	if (mode & 1){
		packet->rmode=(end_func!=0);
		client->hdr.tid=-1;
		if (SifSendCmd(0x8000000A, packet, 0x40, send, client->buff, ssize))
			return 0;
		return -2;
	}else{
		packet->rmode=1;
		client->hdr.tid=GetThreadId();
		if (SifSendCmd(0x8000000A, packet, 0x40, send, client->buff, ssize)==0)
			return -2;
		SleepThread();
		return 0;
	}
}