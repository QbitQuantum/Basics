void CThorTransferGroup::send(SocketEndpoint &ep, CThorRowArray & group)
{
    ISocket * sendSkt = ISocket::connect_wait(ep, 360*120*1000); // give it plenty of time, sequential in nature *could* be delayed in other side listening
    sendSkt->set_block_mode(BF_SYNC_TRANSFER_PULL,0,TRANSFER_TIMEOUT);
    MemoryBuffer mb;
    group.serialize(serializer,mb,false);
    sendSkt->send_block(mb.toByteArray(),mb.length());
    sendSkt->close();
    sendSkt->Release();
}