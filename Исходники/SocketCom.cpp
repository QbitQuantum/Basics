bool SocketCom::Open()
{
	if (server)
	{
#ifdef TRACE
		printf("Opening server\n");
#endif
		Socket listener;
		if (!listener.Create()) return false;
#ifdef TRACE
		printf("Create OK\n");
#endif
		if (!listener.Bind(port)) return false;
#ifdef TRACE
		printf("Binding OK\n");
#endif
		if (!listener.Listen()) return false;
#ifdef TRACE
		printf("Listening OK\n");
#endif
		if (!listener.Accept(*this)) return false;
#ifdef TRACE
		printf("Accept OK\n");
#endif
	}
	else
	{
#ifdef TRACE
		printf("Opening client %s:%d\n",host,port);
#endif
		if (!Create()) return false;
#ifdef TRACE
	printf("Create OK\n");
#endif
		if (!Connect(host,port)) return false;
#ifdef TRACE
		printf("Connect OK\n");
#endif
		SetNonBlocking(true);
	}
	return true;
}