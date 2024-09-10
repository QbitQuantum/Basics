//-------------------------------------------------------------------------------------
void LogWatcher::onMessage(LOG_ITEM* pLogItem)
{
	if(!VALID_COMPONENT(pLogItem->componentType) || filterOptions_.componentBitmap[pLogItem->componentType] == 0)
		return;

	if(filterOptions_.uid != pLogItem->uid)
		return;

	if((filterOptions_.logtypes & pLogItem->logtype) <= 0)
		return;

	if(filterOptions_.globalOrder > 0 && filterOptions_.globalOrder != pLogItem->componentGlobalOrder)
		return;

	if(filterOptions_.groupOrder > 0 && filterOptions_.groupOrder != pLogItem->componentGroupOrder)
		return;

	Network::Channel* pChannel = Logger::getSingleton().networkInterface().findChannel(addr_);

	if(pChannel == NULL)
		return;

	if(!validDate_(pLogItem->logstream.str()) || !containKeyworlds_(pLogItem->logstream.str()))
		return;

	Network::Bundle* pBundle = Network::Bundle::createPoolObject();
	ConsoleInterface::ConsoleLogMessageHandler msgHandler;
	(*pBundle).newMessage(msgHandler);
	(*pBundle) << pLogItem->logstream.str().c_str();
	pChannel->send(pBundle);
}