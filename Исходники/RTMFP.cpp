void RTMFP::Encode(AESEngine& aesEncrypt,PacketWriter packet) {
	// paddingBytesLength=(0xffffffff-plainRequestLength+5)&0x0F
	int paddingBytesLength = (0xFFFFFFFF-packet.length()+5)&0x0F;
	// Padd the plain request with paddingBytesLength of value 0xff at the end
	packet.reset(packet.length());
	string end(paddingBytesLength,(UInt8)0xFF);
	packet.writeRaw(end);
	// Compute the CRC and add it at the beginning of the request
	PacketReader reader(packet);
	reader.next(6);
	UInt16 sum = CheckSum(reader);
	packet.reset(4);packet << sum;
	
	// Encrypt the resulted request
	reader.reset(4);
	aesEncrypt.process(reader.current(),reader.current(),reader.available());
}