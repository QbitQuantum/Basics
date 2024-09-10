void SocketReactor::run()
{
	_pThread = Thread::current();

	Socket::SocketList readable;
	Socket::SocketList writable;
	Socket::SocketList except;
	
	while (!_stop)
	{
		try
		{
			readable.clear();
			writable.clear();
			except.clear();
			int nSockets = 0;
			{
				FastMutex::ScopedLock lock(_mutex);
				for (EventHandlerMap::iterator it = _handlers.begin(); it != _handlers.end(); ++it)
				{
					if (it->second->accepts(_pReadableNotification))
					{
						readable.push_back(it->first);
						nSockets++;
					}
					if (it->second->accepts(_pWritableNotification))
					{
						writable.push_back(it->first);
						nSockets++;
					}
					if (it->second->accepts(_pErrorNotification))
					{
						except.push_back(it->first);
						nSockets++;
					}
				}
			}
			if (nSockets == 0)
			{
				onIdle();
				Thread::trySleep(static_cast<long>(_timeout.totalMilliseconds()));
			}
			else if (Socket::select(readable, writable, except, _timeout))
			{
				onBusy();

				for (Socket::SocketList::iterator it = readable.begin(); it != readable.end(); ++it)
					dispatch(*it, _pReadableNotification);
				for (Socket::SocketList::iterator it = writable.begin(); it != writable.end(); ++it)
					dispatch(*it, _pWritableNotification);
				for (Socket::SocketList::iterator it = except.begin(); it != except.end(); ++it)
					dispatch(*it, _pErrorNotification);
			}
			else onTimeout();
		}
		catch (Exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (std::exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (...)
		{
			ErrorHandler::handle();
		}
	}
	onShutdown();
}