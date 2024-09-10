void CIOCPSocket2::SendCompressingPacket(Packet *pkt)
{
	// Data's too short to bother with compression...
	if (pkt->size() < 500)
	{
		Send(pkt);
		return;
	}

	// TO-DO: Replace this with LZF (again), so much simpler.
	CCompressMng comp;
	ByteBuffer buff(pkt->size() + 1);
	buff << pkt->GetOpcode() << *pkt;
	comp.PreCompressWork((const char *)buff.contents(), buff.size());
	comp.Compress();

	Packet result(WIZ_COMPRESS_PACKET);
	result << uint16(comp.m_nOutputBufferCurPos) << uint16(comp.m_nOrgDataLength) << uint32(comp.m_dwCrc);
	result.append(comp.m_pOutputBuffer, comp.m_nOutputBufferCurPos);
	Send(&result);
}