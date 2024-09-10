RESULT eDVBResourceManager::allocateChannel(const eDVBChannelID &channelid, eUsePtr<iDVBChannel> &channel, bool simulate)
{
		/* first, check if a channel is already existing. */
	std::list<active_channel> &active_channels = simulate ? m_active_simulate_channels : m_active_channels;

	if (!simulate && m_cached_channel)
	{
		eDVBChannel *cache_chan = (eDVBChannel*)&(*m_cached_channel);
		if(channelid==cache_chan->getChannelID())
		{
			eDebug("use cached_channel");
			channel = m_cached_channel;
			return 0;
		}
		m_cached_channel_state_changed_conn.disconnect();
		m_cached_channel=0;
		m_releaseCachedChannelTimer->stop();
	}

	eDebugNoSimulate("allocate channel.. %04x:%04x", channelid.transport_stream_id.get(), channelid.original_network_id.get());
	for (std::list<active_channel>::iterator i(active_channels.begin()); i != active_channels.end(); ++i)
	{
		eDebugNoSimulate("available channel.. %04x:%04x", i->m_channel_id.transport_stream_id.get(), i->m_channel_id.original_network_id.get());
		if (i->m_channel_id == channelid)
		{
			eDebugNoSimulate("found shared channel..");
			channel = i->m_channel;
			return 0;
		}
	}

	/* no currently available channel is tuned to this channelid. create a new one, if possible. */

	if (!m_list)
	{
		eDebugNoSimulate("no channel list set!");
		return errNoChannelList;
	}

	ePtr<iDVBFrontendParameters> feparm;
	if (m_list->getChannelFrontendData(channelid, feparm))
	{
		eDebugNoSimulate("channel not found!");
		return errChannelNotInList;
	}

	/* allocate a frontend. */

	ePtr<eDVBAllocatedFrontend> fe;

	int err = allocateFrontend(fe, feparm, simulate);
	if (err)
		return err;

	RESULT res;
	ePtr<eDVBChannel> ch = new eDVBChannel(this, fe);

	res = ch->setChannel(channelid, feparm);
	if (res)
	{
		channel = 0;
		return errChidNotFound;
	}

	if (simulate)
		channel = ch;
	else
	{
		m_cached_channel = channel = ch;
		m_cached_channel_state_changed_conn =
			CONNECT(ch->m_stateChanged,eDVBResourceManager::DVBChannelStateChanged);
	}

	return 0;
}