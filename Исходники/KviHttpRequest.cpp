bool KviHttpRequest::doConnect()
{
	m_p->uPort = m_url.port();
	if(m_p->uPort == 0)
		m_p->uPort = m_p->bIsSSL ? 443 : 80;

	if(m_p->pSocket)
		closeSocket();
#ifdef COMPILE_SSL_SUPPORT
	m_p->pSocket = m_p->bIsSSL ? new QSslSocket() : new QTcpSocket();
#else
	m_p->pSocket = new QTcpSocket();
#endif
	QObject::connect(m_p->pSocket,SIGNAL(connected()),this,SLOT(slotSocketConnected()));
	QObject::connect(m_p->pSocket,SIGNAL(disconnected()),this,SLOT(slotSocketDisconnected()));
	QObject::connect(m_p->pSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotSocketError(QAbstractSocket::SocketError)));
	QObject::connect(m_p->pSocket,SIGNAL(readyRead()),this,SLOT(slotSocketReadDataReady()));
	QObject::connect(m_p->pSocket,SIGNAL(hostFound()),this,SLOT(slotSocketHostResolved()));

	emit resolvingHost(m_url.host());

#ifdef COMPILE_SSL_SUPPORT
	if(m_p->bIsSSL)
	{
		static_cast<QSslSocket *>(m_p->pSocket)->setProtocol(QSsl::AnyProtocol);
		static_cast<QSslSocket *>(m_p->pSocket)->connectToHostEncrypted(m_url.host(),m_p->uPort);
	} else {
		m_p->pSocket->connectToHost(m_url.host(),m_p->uPort);
	}
#else
	m_p->pSocket->connectToHost(m_url.host(),m_p->uPort);
#endif


	if(m_p->pConnectTimeoutTimer)
	{
		delete m_p->pConnectTimeoutTimer;
		m_p->pConnectTimeoutTimer = NULL;
	}

	m_p->pConnectTimeoutTimer = new QTimer();
	m_p->pConnectTimeoutTimer->setSingleShot(true);
	QObject::connect(m_p->pConnectTimeoutTimer,SIGNAL(timeout()),this,SLOT(slotConnectionTimedOut()));

	m_p->pConnectTimeoutTimer->start(m_uConnectionTimeout * 1000);

	/*
	m_pThread = new KviHttpRequestThread(
			this,
			m_url.host(),
			m_szIp,
			uPort,
			m_url.path(),
			m_uContentOffset,
			(m_eProcessingType == HeadersOnly) ? KviHttpRequestThread::Head : (m_szPostData.isEmpty() ? KviHttpRequestThread::Get : KviHttpRequestThread::Post),
			m_szPostData,
			m_url.protocol()=="https"
		);
	*/


	return true;
}