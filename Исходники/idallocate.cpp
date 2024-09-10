//-------------------------------------------------------------------------------------
void EntityIDClient::onAlloc(void)
{
	if(size() > id_enough_limit)
	{
		setReqServerAllocFlag(false);
		return;
	}
	
	if(hasReqServerAlloc())
		return;

	Network::Channel* pChannel = Components::getSingleton().getDbmgrChannel();

	if(pChannel == NULL)
	{
		ERROR_MSG("EntityIDClient::onAlloc: not found dbmgr!\n");
		return;
	}

	Network::Bundle* pBundle = Network::Bundle::createPoolObject();
	(*pBundle).newMessage(DbmgrInterface::onReqAllocEntityID);
	DbmgrInterface::onReqAllocEntityIDArgs2::staticAddToBundle((*pBundle), pApp_->componentType(), pApp_->componentID());
	pChannel->send(pBundle);

	setReqServerAllocFlag(true);

	WARNING_MSG(fmt::format("EntityIDClient::onAlloc: not enough({}) entityIDs!\n", id_enough_limit));
}