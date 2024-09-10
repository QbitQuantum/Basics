void CFrameDump::Write(Framework::CStream& output) const
{
	Framework::CZipArchiveWriter archive;

	archive.InsertFile(new CMemoryStateFile(STATE_INITIAL_GSRAM, m_initialGsRam, CGSHandler::RAMSIZE));
	archive.InsertFile(new CMemoryStateFile(STATE_INITIAL_GSREGS, m_initialGsRegisters, sizeof(uint64) * CGSHandler::REGISTER_MAX));

	{
		auto privRegsStateFile = new CRegisterStateFile(STATE_INITIAL_GSPRIVREGS);
		privRegsStateFile->SetRegister64(STATE_PRIVREG_SMODE2, m_initialSMODE2);
		archive.InsertFile(privRegsStateFile);
	}

	unsigned int currentPacket = 0;
	for(const auto& packet : m_packets)
	{
		auto packetMetadataFileName = STATE_PACKET_METADATA_PREFIX + std::to_string(currentPacket);
		archive.InsertFile(new CMemoryStateFile(packetMetadataFileName.c_str(), &packet.metadata, sizeof(CGsPacketMetadata)));
		if(!packet.registerWrites.empty())
		{
			auto packetRegisterWritesFileName = STATE_PACKET_REGISTERWRITES_PREFIX + std::to_string(currentPacket);
			archive.InsertFile(new CMemoryStateFile(packetRegisterWritesFileName.c_str(), packet.registerWrites.data(), packet.registerWrites.size() * sizeof(CGSHandler::RegisterWrite)));
		}
		if(!packet.imageData.empty())
		{
			auto packetImageDataName = STATE_PACKET_IMAGEDATA_PREFIX + std::to_string(currentPacket);
			archive.InsertFile(new CMemoryStateFile(packetImageDataName.c_str(), packet.imageData.data(), packet.imageData.size()));
		}
		currentPacket++;
	}

	archive.Write(output);
}