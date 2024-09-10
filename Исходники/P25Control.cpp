void CP25Control::createRFHeader()
{
	unsigned char buffer[P25_HDR_FRAME_LENGTH_BYTES + 2U];
	::memset(buffer, 0x00U, P25_HDR_FRAME_LENGTH_BYTES + 2U);

	buffer[0U] = TAG_HEADER;
	buffer[1U] = 0x00U;

	// Add the sync
	CSync::addP25Sync(buffer + 2U);

	// Add the NID
	m_nid.encode(buffer + 2U, P25_DUID_HEADER);

	// Add the dummy header
	m_rfData.encodeHeader(buffer + 2U);

	// Add busy bits
	addBusyBits(buffer + 2U, P25_HDR_FRAME_LENGTH_BITS, false, true);

	m_rfFrames = 0U;
	m_rfErrs = 0U;
	m_rfBits = 1U;
	m_rfTimeout.start();
	m_lastDUID = P25_DUID_HEADER;
	::memset(m_rfLDU, 0x00U, P25_LDU_FRAME_LENGTH_BYTES);

#if defined(DUMP_P25)
	openFile();
	writeFile(buffer + 2U, buffer - 2U);
#endif

	if (m_duplex) {
		buffer[0U] = TAG_HEADER;
		buffer[1U] = 0x00U;
		writeQueueRF(buffer, P25_HDR_FRAME_LENGTH_BYTES + 2U);
	}
}