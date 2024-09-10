//-------------------------------------------------------------------------------------
bool EntityAutoLoader::process()
{
	Network::Channel* pChannel = Components::getSingleton().getDbmgrChannel();
	if(pChannel == NULL || querying_)
		return true;

	if(entityTypes_.size() > 0)
	{
		if ((*entityTypes_.begin()).size() > 0)
		{
			Network::Bundle* pBundle = Network::Bundle::ObjPool().createObject();

			if (start_ == 0 && end_ == 0)
				end_ = LOAD_ENTITY_SIZE;

			uint16 dbInterfaceIndex = g_kbeSrvConfig.getDBMgr().dbInterfaceInfos.size() - entityTypes_.size();
			(*pBundle).newMessage(DbmgrInterface::entityAutoLoad);
			(*pBundle) << dbInterfaceIndex << g_componentID << (*(*entityTypes_.begin()).begin()) << start_ << end_;
			pChannel->send(pBundle);
			querying_ = true;
		}
		else
		{
			entityTypes_.erase(entityTypes_.begin());
		}

		return true;
	}

	delete this;
	return false;
}