void
SocketIOQueue::PostTerminationSignal(){
	if( m_hIOCP == NULL )
		return;
	PostQueuedCompletionStatus(m_hIOCP, 0, NULL, NULL);
	}