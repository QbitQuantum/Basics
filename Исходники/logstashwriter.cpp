void LogstashWriter::ReconnectTimerHandler(void)
{
 	if (m_Stream)
		return;

	Socket::Ptr socket;

	if (GetSocketType() == "tcp")
		socket = new TcpSocket();
	else
		socket = new UdpSocket();

	Log(LogNotice, "LogstashWriter")
	    << "Reconnecting to Logstash endpoint '" << GetHost() << "' port '" << GetPort() << "'.";

	try {
		socket->Connect(GetHost(), GetPort());
	} catch (const std::exception&) {
		Log(LogCritical, "LogstashWriter")
		    << "Can't connect to Logstash endpoint '" << GetHost() << "' port '" << GetPort() << "'.";
		return;
	}

	m_Stream = new NetworkStream(socket);
}