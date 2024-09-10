//-------------------------------------------------------------------------------------
void GlobalDataClient::onDataChanged(PyObject* key, PyObject* value, bool isDelete)
{
	std::string skey = script::Pickler::pickle(key, 0);
	std::string sval = "";

	if(value)
		sval = script::Pickler::pickle(value, 0);

	Components::COMPONENTS& channels = Components::getSingleton().getComponents(serverComponentType_);
	Components::COMPONENTS::iterator iter1 = channels.begin();
	uint8 dataType = dataType_;
	ArraySize slen = 0;

	for(; iter1 != channels.end(); ++iter1)
	{
		Network::Channel* lpChannel = iter1->pChannel;
		KBE_ASSERT(lpChannel != NULL);
		
		Network::Bundle* pBundle = Network::Bundle::createPoolObject();
		
		(*pBundle).newMessage(DbmgrInterface::onBroadcastGlobalDataChanged);
		
		(*pBundle) << dataType;
		(*pBundle) << isDelete;

		slen = skey.size();
		(*pBundle) << slen;
		(*pBundle).assign(skey.data(), slen);

		if(!isDelete)
		{
			slen = sval.size();
			(*pBundle) << slen;
			(*pBundle).assign(sval.data(), slen);
		}

		(*pBundle) << g_componentType;

		lpChannel->send(pBundle);
	}
}