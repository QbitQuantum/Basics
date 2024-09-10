//----------------------------------------------------------------------------
void ServerPoll::_ReadWriteRun()
{
	Socket::SocketList readable;
	Socket::SocketList writable;
	Socket::SocketList except;
	std::map<px2_socket_t, ClientContext*> contextMap;

	int nSockets = 0;
	{
		ScopedCS cs(&mContextMapMutex);

		std::map<unsigned int, ClientContext *>::iterator it = mClientMap.begin();
		for (; it != mClientMap.end(); it++)
		{
			contextMap[it->second->TheSocket.GetSocket()] = it->second;

			readable.push_back(it->second->TheSocket);
			writable.push_back(it->second->TheSocket);
			except.push_back(it->second->TheSocket);

			nSockets++;
		}
	}

	Timespan timeout(250000);
	if (nSockets == 0)
	{
		// odle
		/*_*/
	}
	else if (Socket::Select(readable, writable, except, timeout))
	{
		// busy

		for (Socket::SocketList::iterator it = readable.begin(); it != readable.end(); ++it)
		{
			ClientContext *context = contextMap[(*it).GetSocket()];
			if (_OnRead(context) < 0)
			{
				DisconnectClient(context->ClientID);
			}
		}

		for (Socket::SocketList::iterator it = writable.begin(); it != writable.end(); ++it)
		{
			ClientContext *context = contextMap[(*it).GetSocket()];
			if (_OnWrite(context) < 0)
			{
				DisconnectClient(context->ClientID);
			}
		}

		for (Socket::SocketList::iterator it = except.begin(); it != except.end(); ++it)
		{
		}
	}
	else
	{
		// time out
		/*_*/
	}
}