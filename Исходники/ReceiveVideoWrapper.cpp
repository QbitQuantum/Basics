void H264RtpToAnxbCb::TransmitAnxbFrame(const uint8_t *data, uint32_t len, int timestamp_ms) {
	m_FrameCnt++;
	PACKET_DBG("To decoder: frame len %d bytes,  received_frame_cnt: %d, timestamp_ms: %d", len, m_FrameCnt, timestamp_ms);

	m_pReceive.m_ReceiveFStat.Update();
	if (m_pReceive.m_ReceiveFStat.IsValid())
		TI_DBG("Receive Framerate: %s", m_pReceive.m_ReceiveFStat.GetStatStr());

	if (Configuration::GetCfg()->GetIntVal("DumpReceiveAnxbPackets")) {
		m_pReceive.m_pReceiveAnxbDump->StorePacket(data, len);
	}

#ifndef MINIMAL_MODE
	if (Configuration::GetCfg()->GetIntVal("RenderVideo")) {
		VideoData frame;
		frame.SetBuf(data, len);
		frame.SetTimestamp(timestamp_ms);
		m_pReceive.m_pDecoder->DecodeFrame(frame);
	}
#endif
}