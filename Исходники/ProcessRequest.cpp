UINT WINAPI ProcessConnection(LPVOID arg) {
	SOCKET connectSocket = (SOCKET) arg;
	HttpConnection connection;

	ConnectionInit(&connection, connectSocket);
	while (TRUE) {
		if (!ContextInit(&connection.ctx,  &connection) )
			break;
#ifdef _DEBUG	
		showContext(&connection.ctx);
#endif
	 
		ProcessRequest(&connection.ctx);
			
		if (strcmp("Keep-Alive", HeaderGet(&connection.ctx.reqList, "Connection"))) {
			break;
		}
#ifdef _DEBUG
		printf("Processing done!\n");
#endif
	}
	
    ConnectionClose(&connection);
#ifdef _DEBUG
	_tprintf(_T("release connection!\n"));
#endif	
	return 0;
}