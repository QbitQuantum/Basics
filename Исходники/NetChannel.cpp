bool NetChannel::StartChannel()
{
	if(!NetChannelBase::StartChannel())
		return false;

	assert( m_hExitSending.IsValid() && m_hExitReceiving.IsValid() );

	m_socket.SetNonBlocking(false);

	if(!BindIoCompletionCallback( (HANDLE)m_socket.GetSocket(), AsynIoCompleteProc, 0))
		return false;

	m_pRecvBuffer = new BYTE[m_sockRcBuffSize];
	if( !m_pRecvBuffer)
		return false;

	{
		MYOVERLAPPED& olp = m_OLPSend;
		memset( &olp, 0, sizeof(MYOVERLAPPED));

		olp.pChannel = this;
		olp.bSend = true;
	}

	{
		MYOVERLAPPED& olp = m_OLPRecv;
		memset( &olp, 0, sizeof(MYOVERLAPPED));
		olp.pChannel = this;
		olp.bSend = false;
	}

	if(!StartNewRecv( sizeof( BlockHeadT)))
		return false;

	return true;
}