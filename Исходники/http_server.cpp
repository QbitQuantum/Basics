bool HTTPServer::start()
{
	Socket::initWinsocks();
	
	Socket mainSocket;
	mainSocket.create();
	
	if (!mainSocket.bind(m_port))
	{
		printf("Couldn't bind to port: %i\n", m_port);
		return false;
	}
	
	if (!mainSocket.listen(20))
	{
		printf("Couldn't listen for connections.\n");
		return false;
	}
	
	createNeededTables(m_pMainDB);
	
	while (true)
	{
		Socket *newSock = new Socket();
		if (mainSocket.accept(newSock))
		{
			HTTPServerRequestThread *newThread = new HTTPServerRequestThread(newSock, m_webContentPath, m_pMainDB);
			
			if (newThread)
			{
				newThread->setAutodestruct(true);
				newThread->start();
			}
			else
			{
				printf("Couldn't create new thread\n");
			}
		}
		else
		{
			printf("Couldn't accept connection\n");
		}
	}
		
	Socket::cleanupWinsocks();
	return true;
}