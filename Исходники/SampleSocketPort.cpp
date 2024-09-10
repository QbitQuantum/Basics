SampleSocketPort::SampleSocketPort(SocketService *pService, TCPSocket & tcpSocket) : 
				SocketPort(pService, tcpSocket)
{
	tpport_t port;
	InetHostAddress ia = getPeer( & port );
	cerr << "connecting from " << ia.getHostname() << ":" << port << endl;

	// Set up non-blocking reads
	setCompletion( false );

	//1.9.3 THIS LINE DOES NOT SEEM TO BE REQUIRED ANYMORE!
	//This sorts out a bug which prevents connections after a disconnect
	//setDetectOutput(true);

	m_bOpen = true;
	m_bDoDisconnect = false;
	m_bTimedOut = false;
	m_bReceptionStarted = false;
	m_nLastBytesAvail = 0;
	m_pBuf = new char[MAX_RXBUF];
}