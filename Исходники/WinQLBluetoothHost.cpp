	//--------------------------------------------------------------------------------
	void CBluetoothHost::StopMonitoringRadios()
	{
		_WINQ_FCONTEXT( "CBluetoothHost::StopMonitoringRadios" );
		CMessageHandler MessageHandler;
		MessageHandler.PostToThread( m_ulMonitorThreadID, COSWindow::wmQuit, 0, 0 );
		CWaitHelper WaitHelper;
		WaitHelper.WaitForSingleObject( m_pBluetoothHostMonitorThread->Handle(), Infinite );
		delete m_pBluetoothHostMonitorThread;
		m_pBluetoothHostMonitorThread = 0;
	}