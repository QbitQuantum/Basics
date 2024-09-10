//-------------------------------------------------------------------------------------
bool BillingHandler_ThirdParty::reconnect()
{
	if(pBillingChannel_)
	{
		if(!pBillingChannel_->isDestroyed())
			Dbmgr::getSingleton().networkInterface().deregisterChannel(pBillingChannel_);

		pBillingChannel_->decRef();
	}

	Network::Address addr = g_kbeSrvConfig.billingSystemAddr();
	Network::EndPoint* pEndPoint = new Network::EndPoint(addr);

	pEndPoint->socket(SOCK_STREAM);
	if (!pEndPoint->good())
	{
		ERROR_MSG("BillingHandler_ThirdParty::initialize: couldn't create a socket\n");
		return true;
	}

	pEndPoint->setnonblocking(true);
	pEndPoint->setnodelay(true);

	pBillingChannel_ = new Network::Channel(Dbmgr::getSingleton().networkInterface(), pEndPoint, Network::Channel::INTERNAL);
	pBillingChannel_->incRef();

	int trycount = 0;

	while(true)
	{
		fd_set	frds, fwds;
		struct timeval tv = { 0, 100000 }; // 100ms

		FD_ZERO( &frds );
		FD_ZERO( &fwds );
		FD_SET((int)(*pBillingChannel_->endpoint()), &frds);
		FD_SET((int)(*pBillingChannel_->endpoint()), &fwds);

		if(pBillingChannel_->endpoint()->connect() == -1)
		{
			int selgot = select((*pBillingChannel_->endpoint())+1, &frds, &fwds, NULL, &tv);
			if(selgot > 0)
			{
				break;
			}

			trycount++;

			if(trycount > 3)
			{
				ERROR_MSG(fmt::format("BillingHandler_ThirdParty::reconnect(): couldn't connect to:{}\n", 
					pBillingChannel_->endpoint()->addr().c_str()));
				
				pBillingChannel_->destroy();
				return false;
			}
		}
	}

	// 不检查超时
	pBillingChannel_->stopInactivityDetection();
	Dbmgr::getSingleton().networkInterface().registerChannel(pBillingChannel_);
	return true;
}