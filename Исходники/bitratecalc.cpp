eBitrateCalc::eBitrateCalc(int pid, int dvbnamespace, int tsid, int onid, int refreshintervall, int buffer_size): m_size(0), m_refresh_intervall(refreshintervall)
{
	m_send_data_timer = eTimer::create(eApp);
	CONNECT(m_send_data_timer->timeout, eBitrateCalc::sendDataTimerTimeoutCB);
	eDVBChannelID chid; //(eDVBNamespace(dvbnamespace), eTransportStreamID(tsid), eOriginalNetworkID(onid));  <-- weird, that does not work
	chid.dvbnamespace = eDVBNamespace(dvbnamespace);
	chid.transport_stream_id = eTransportStreamID(tsid);
	chid.original_network_id = eOriginalNetworkID(onid);
	ePtr<eDVBResourceManager> res_mgr;
	eDVBResourceManager::getInstance(res_mgr);
	eUsePtr<iDVBChannel> channel;
	int success = 0;
	m_reader = NULL;
	if (!res_mgr->allocateChannel(chid, channel, false))
	{
		ePtr<iDVBDemux> demux;
		if (!channel->getDemux(demux))
		{
			if (!demux->createPESReader(eApp, m_reader))
			{
				if (!m_reader->connectRead(slot(*this, &eBitrateCalc::dataReady), m_pes_connection))
				{
					channel->connectStateChange(slot(*this, &eBitrateCalc::stateChange), m_channel_connection);
					success = 1;
				}
				else
					eDebug("[eBitrateCalc] connect pes reader failed...");
			}
			else
				eDebug("[eBitrateCalc] create PES reader failed...");
		}
		else 
			eDebug("[eBitrateCalc] getDemux failed...");
	}
	else
	{
		eDebug("[eBitrateCalc] allocate channel failed...trying pvr_allocate_demux");
		ePtr<eDVBAllocatedDemux> pvr_allocated_demux;
		int i = 0;
		if (!res_mgr->allocateDemux(NULL,pvr_allocated_demux,i))
		{
			eDVBDemux &demux = pvr_allocated_demux->get();
			if (!demux.createPESReader(eApp, m_reader))
			{
				if (!m_reader->connectRead(slot(*this, &eBitrateCalc::dataReady), m_pes_connection))
					success = 1;
				else
					eDebug("[eBitrateCalc] connect pes reader failed...");
			}
			else
				eDebug("[eBitrateCalc] create PES reader failed...");
		}
		else
			eDebug("[eBitrateCalc] allocate pvr_allocated_demux failed...");
	}
	if (m_reader and success)
	{
		clock_gettime(CLOCK_MONOTONIC, &m_start);
		m_reader->setBufferSize(buffer_size);
		m_reader->start(pid);
		m_send_data_timer->start(m_refresh_intervall, true);
	}
	else
		sendData(-1,0);
}