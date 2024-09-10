void iMX27RtpInterface::FrameReceived(const Sid::Binary & data, int timestamp_ms) {
	PACKET_DBG("Received frame, len %d, count", data.size(), m_ReceiveFcnt);
	m_ReceiveFcnt++;

	m_ReceiveBStat.Update(data.getSize());
	if (m_ReceiveBStat.IsValid())
		RTP_DBG("Receive bitrate: %s", m_ReceiveBStat.GetStatStr());

	if (Configuration::GetCfg()->GetIntVal("UseLoopback")) {
		if (m_RecordingStarted) {
			VideoData frame;
			frame.SetBuf((const uint8_t*)data.data(), data.size());
			frame.SetTimestamp(timestamp_ms);
			TransportSendFrame(frame);
		}
		return;
	}

	if (m_pReceiveWrapper) {
		VideoData frame;
		frame.SetBuf((uint8_t *)data.data(), data.size());
		frame.SetTimestamp(timestamp_ms);
		m_pReceiveWrapper->SubmitFrame(frame);
	}
	return;
}