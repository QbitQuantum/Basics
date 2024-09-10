int cellAudioGetPortTimestamp(u32 portNum, u64 tag, mem64_t stamp)
{
	cellAudio.Log("cellAudioGetPortTimestamp(portNum=0x%x, tag=0x%llx, stamp_addr=0x%x)", portNum, tag, stamp.GetAddr());

	if (portNum >= m_config.AUDIO_PORT_COUNT) 
	{
		return CELL_AUDIO_ERROR_PARAM;
	}

	if (!m_config.m_ports[portNum].m_is_audio_port_opened)
	{
		return CELL_AUDIO_ERROR_PORT_NOT_OPEN;
	}

	if (!m_config.m_ports[portNum].m_is_audio_port_started)
	{
		return CELL_AUDIO_ERROR_PORT_NOT_RUN;
	}

	AudioPortConfig& port = m_config.m_ports[portNum];

	SMutexGeneralLocker lock(port.m_mutex);

	stamp = m_config.start_time + (port.counter + (tag - port.tag)) * 256000000 / 48000;

	return CELL_OK;
}