void UnInitSock()   
{   
	if (g_wsaEvent != WSA_INVALID_EVENT)   
	{   
		WSACloseEvent(g_wsaEvent);   
	}   
	if (g_socketServer != INVALID_SOCKET)   
	{   
		closesocket(g_socketServer);   
		g_socketServer = INVALID_SOCKET; 
	}   
	WSACleanup();   


}   