void DropsPacket::drop(vector <Player*> players, Drop* drop, Dropped dropper){
	Packet packet = Packet();
	packet.addHeader(0xB9);
	packet.addByte(1);
	packet.addInt(drop->getObjID());
	packet.addByte(drop->getMesos());
	packet.addInt(drop->getID());
	packet.addInt(dropper.id);
	packet.addByte(0);
	packet.addShort(drop->getPos().x);
	packet.addShort(drop->getPos().y);
	packet.addInt(0); //Time till
	packet.addShort(dropper.pos.x);
	packet.addShort(dropper.pos.y);
	packet.addShort(0);
	packet.addByte(0);
	if(!drop->getMesos()){
		packet.addBytes("8005BB46E6170200");
	}
	packet.sendTo(NULL, players, 1);
}