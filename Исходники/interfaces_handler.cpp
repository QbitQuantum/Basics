//-------------------------------------------------------------------------------------
bool InterfacesHandler_Interfaces::reconnect()
{
	Network::Channel* pInterfacesChannel = Dbmgr::getSingleton().networkInterface().findChannel(g_kbeSrvConfig.interfacesAddr());

	if(pInterfacesChannel)
	{
		if(!pInterfacesChannel->isDestroyed())
			Dbmgr::getSingleton().networkInterface().deregisterChannel(pInterfacesChannel);

		pInterfacesChannel->destroy();
		Network::Channel::reclaimPoolObject(pInterfacesChannel);
	}

	Network::Address addr = g_kbeSrvConfig.interfacesAddr();
	Network::EndPoint* pEndPoint = Network::EndPoint::createPoolObject();
	pEndPoint->addr(addr);

	pEndPoint->socket(SOCK_STREAM);
	if (!pEndPoint->good())
	{
		ERROR_MSG("InterfacesHandler_Interfaces::initialize: couldn't create a socket\n");
		return true;
	}

	pEndPoint->setnonblocking(true);
	pEndPoint->setnodelay(true);

	pInterfacesChannel = Network::Channel::createPoolObject();
	bool ret = pInterfacesChannel->initialize(Dbmgr::getSingleton().networkInterface(), pEndPoint, Network::Channel::INTERNAL);
	if(!ret)
	{
		ERROR_MSG(fmt::format("InterfacesHandler_Interfaces::initialize: initialize({}) is failed!\n",
			pInterfacesChannel->c_str()));

		pInterfacesChannel->destroy();
		Network::Channel::reclaimPoolObject(pInterfacesChannel);
		return 0;
	}

	if(pInterfacesChannel->pEndPoint()->connect() == -1)
	{
		struct timeval tv = { 0, 1000000 }; // 1000ms
		fd_set	fds;
		FD_ZERO(&fds);
		FD_SET((int)(*pInterfacesChannel->pEndPoint()), &fds);

		bool connected = false;
		int selgot = select((*pInterfacesChannel->pEndPoint())+1, &fds, &fds, NULL, &tv);
		if(selgot > 0)
		{
			int error;
			socklen_t len = sizeof(error);
#if KBE_PLATFORM == PLATFORM_WIN32
			getsockopt(int(*pInterfacesChannel->pEndPoint()), SOL_SOCKET, SO_ERROR, (char*)&error, &len);
#else
			getsockopt(int(*pInterfacesChannel->pEndPoint()), SOL_SOCKET, SO_ERROR, &error, &len);
#endif
			if(0 == error)
				connected = true;
		}

		if(!connected)
		{
			ERROR_MSG(fmt::format("InterfacesHandler_Interfaces::reconnect(): couldn't connect to:{}\n", 
				pInterfacesChannel->pEndPoint()->addr().c_str()));

			pInterfacesChannel->destroy();
			Network::Channel::reclaimPoolObject(pInterfacesChannel);
			return false;
		}
	}

	// 不检查超时
	pInterfacesChannel->stopInactivityDetection();
	Dbmgr::getSingleton().networkInterface().registerChannel(pInterfacesChannel);
	return true;
}