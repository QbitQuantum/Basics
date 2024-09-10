//-------------------------------------------------------------------------------------
bool DelayedChannels::process()
{
	ChannelAddrs::iterator iter = channeladdrs_.begin();

	while (iter != channeladdrs_.end())
	{
		Channel * pChannel = pNetworkInterface_->findChannel((*iter));

		if (pChannel && (!pChannel->isCondemn() && !pChannel->isDestroyed()))
		{
			pChannel->send();
		}

		++iter;
	}

	channeladdrs_.clear();
	return true;
}