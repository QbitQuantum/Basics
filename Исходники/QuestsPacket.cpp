void QuestsPacket::questFinish(Player* player, vector <Player*> players,short questid, int npcid, short nextquest, __int64 time){
	Packet packet = Packet();
	packet.addHeader(0x32);
	packet.addByte(1);
	packet.addShort(questid);
	packet.addByte(2);
	packet.addInt64(time);
	packet.packetSend(player);
	packet = Packet();
	packet.addHeader(0x6D);
	packet.addByte(6);
	packet.addShort(questid); 
	packet.addInt(npcid); 
	packet.addShort(nextquest); 
	packet.packetSend(player);
	packet = Packet();
	packet.addHeader(0x68);
	packet.addByte(9);
	packet.packetSend(player);
	packet = Packet();
	packet.addHeader(0x86);
	packet.addInt(player->getPlayerid());
	packet.addByte(9);
	packet.sendTo(player, players, 0);
}