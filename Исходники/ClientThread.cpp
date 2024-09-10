//-----------------------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------------------
ClientThread::ClientThread(SocketClient* client, int threadId, float interval)
{
	setThreadId(threadId);
	socketClient = client;
	flag = false;

	timer = new FdTimer(getThreadId(), interval);
}