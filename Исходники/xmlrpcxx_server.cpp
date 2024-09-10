void OTSocket::Listen(const OTString &strBind)
{
	if (NULL != m_pSocket)
		delete m_pSocket;
//	m_pSocket = NULL;
	m_pSocket = new zmq::socket_t(*m_pContext, ZMQ_REP);  // RESPONSE socket (Request / Response.)
	OT_ASSERT_MSG(NULL != m_pSocket, "OTSocket::Listen: new zmq::socket(context, ZMQ_REP)");
	
	OTString strTemp(strBind); // In case m_strBindPath is what was passed in. (It happens.)
	m_strBindPath.Set(strTemp); // In case we have to close/reopen the socket to finish a send/receive.
	
	// ------------------------
	//  Configure socket to not wait at close time
    //
	const int linger = 0; // close immediately
	m_pSocket->setsockopt (ZMQ_LINGER, &linger, sizeof (linger));
    /*
     int zmq_setsockopt (void *socket, int option_name, const void *option_value, size_t option_len);
     
     Caution: All options, with the exception of ZMQ_SUBSCRIBE, ZMQ_UNSUBSCRIBE and ZMQ_LINGER, only take effect for subsequent socket bind/connects.     
     */
    
	// ------------------------
    
	m_pSocket->bind(strBind.Get());
}