bool QtLocalPeer::sendMessage(const QString &message, int timeout)
{
	if (!isClient())
		return false;

	QLocalSocket socket;
	bool connOk = false;
	for(int i = 0; i < 2; i++) {
		// Try twice, in case the other instance is just starting up
		socket.connectToServer(socketName);
		connOk = socket.waitForConnected(timeout/2);
		if (connOk || i)
			break;
		int ms = 250;
#if defined(Q_OS_WIN)
		Sleep(DWORD(ms));
#else
		struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
		nanosleep(&ts, NULL);
#endif
	}
	if (!connOk)
		return false;

#if defined(Q_OS_WIN)
	AllowSetForegroundWindow(ASFW_ANY);
#endif

	QByteArray uMsg(message.toUtf8());
	QDataStream ds(&socket);
	ds.writeBytes(uMsg.constData(), uMsg.size());
	bool res = socket.waitForBytesWritten(timeout);
	res &= socket.waitForReadyRead(timeout);   // wait for ack
	res &= (socket.read(qstrlen(ack)) == ack);
	return res;
}