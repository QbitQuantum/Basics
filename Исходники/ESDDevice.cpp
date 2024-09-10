int CESDDevice::init(const char* acInitString)
{
	InitializeCriticalSection(&m_csDevice);
	int i, iRetVal = 0;
	int txTimeOut = 0;
	char* pcToken;
	char acString[128];
	if(m_bInitFlag)
	{
		warning("device already initialized");
		m_iErrorState = ERRID_DEV_ISINITIALIZED;
		return m_iErrorState;
	}
	m_iDeviceId = -1;
	m_iErrorState = 0;
	strncpy(m_acInitString,acInitString,128);
	strncpy(acString,acInitString,128);
	pcToken = strtok( acString, ":" );
	if( !pcToken )
	{	m_iErrorState = ERRID_DEV_BADINITSTRING;
		return m_iErrorState;
	}
	if( strcmp( pcToken, "ESD" ) != 0 )
	{	m_iErrorState = ERRID_DEV_BADINITSTRING;
		return m_iErrorState;
	}
	pcToken = strtok( NULL, "," );
	if( !pcToken )
	{	m_iErrorState = ERRID_DEV_BADINITSTRING;
		return m_iErrorState;
	}
	m_iDeviceId = atoi(pcToken);

	pcToken = strtok( NULL, "," );
	if( !pcToken )
	{	m_iErrorState = ERRID_DEV_BADINITSTRING;
		return m_iErrorState;
	}
	m_iBaudRate = atoi(pcToken);

#if defined(__LINUX__)
	m_uiTimeOut = 6;
#endif
#if defined (_WIN32)
	switch( m_iBaudRate )
	{
	case 125:
	case 250:
		m_uiTimeOut = 4;
		break;
	case 500:
		m_uiTimeOut = 3;
		break;
	case 1000:
		m_uiTimeOut = 2;
		break;
	default:
		m_uiTimeOut = 10;
		break;
	}
#endif

	try
	{
		iRetVal = canOpen(	
					m_iDeviceId,			// Net
					0,						// Mode
					m_uiQueueSize,			// TX Queue
					m_uiQueueSize,			// RX Queue
					m_uiTimeOut,			// Tx Timeout
					m_uiTimeOut,			// Rx Timeout
					&m_hDevice);
		if(iRetVal != NTCAN_SUCCESS)
		{
			warning("can open failed Errorcode: %d", iRetVal);
			getDeviceError(iRetVal);
			m_iErrorState = ERRID_DEV_INITERROR;
			return m_iErrorState;
		}
		iRetVal = canOpen(	
					m_iDeviceId,			// Net
					0,						// Mode
					1,						// TX Queue
					1,						// RX Queue
					600,					// Tx Timeout
					100,					// Rx Timeout
					&m_hSyncDevice);
		if(iRetVal != NTCAN_SUCCESS)
		{
			warning("can open failed Errorcode: %d", iRetVal);
			getDeviceError(iRetVal);
			m_iErrorState = ERRID_DEV_INITERROR;
			return m_iErrorState;
		}
	}
	catch(...)
	{
			warning("init ESD device failed no library found");
			m_iErrorState = ERRID_DEV_NOLIBRARY;
			return m_iErrorState;
	}

	for(i = 0; i <= m_iModuleCountMax; i++)
	{
		iRetVal = canIdAdd(m_hDevice, (MSGID_ACK + i));
		if(iRetVal != NTCAN_SUCCESS)
		{
			warning("can add ID failed Errorcode: %d", iRetVal);
			getDeviceError(iRetVal);
			m_iErrorState = ERRID_DEV_INITERROR;
			return m_iErrorState;
		}
		iRetVal = canIdAdd(m_hDevice, (MSGID_STATE + i));
		if(iRetVal != NTCAN_SUCCESS)
		{
			warning("can add ID failed Errorcode: %d", iRetVal);
			getDeviceError(iRetVal);
			m_iErrorState = ERRID_DEV_INITERROR;
			return m_iErrorState;
		}
	}

	for(i = 0; i <= MAX_MP55; i++ )
	{
		iRetVal = canIdAdd(m_hDevice, (MSGID_MP55_RECV + i));
		if(iRetVal != NTCAN_SUCCESS)
		{
			warning("can add ID failed Errorcode: %d", iRetVal);
			getDeviceError(iRetVal);
			m_iErrorState = ERRID_DEV_INITERROR;
			return m_iErrorState;
		}

		iRetVal = canIdAdd(m_hDevice, (0x180 + i));
		if(iRetVal != NTCAN_SUCCESS)
		{
			warning("can add ID failed Errorcode: %d", iRetVal);
			getDeviceError(iRetVal);
			m_iErrorState = ERRID_DEV_INITERROR;
			return m_iErrorState;
		}
		iRetVal = canIdAdd(m_hDevice, (0x600 + i));
		if(iRetVal != NTCAN_SUCCESS)
		{
			warning("can add ID failed Errorcode: %d", iRetVal);
			getDeviceError(iRetVal);
			m_iErrorState = ERRID_DEV_INITERROR;
			return m_iErrorState;
		}
	}

	for(i = 0; i < MAX_SCHUNK; i++ )
	{
		iRetVal = canIdAdd(m_hDevice, (MSGID_SCHUNK_RECV + i));
		if(iRetVal != NTCAN_SUCCESS)
		{
			warning("can add ID failed Errorcode: %d", iRetVal);
			getDeviceError(iRetVal);
			m_iErrorState = ERRID_DEV_INITERROR;
			return m_iErrorState;
		}
	}
	
	iRetVal = canIdAdd(m_hSyncDevice, MSGID_ALL);
	if(iRetVal != NTCAN_SUCCESS)
	{
		warning("can add ID failed Errorcode: %d", iRetVal);
		getDeviceError(iRetVal);
		m_iErrorState = ERRID_DEV_INITERROR;
		return m_iErrorState;
	}

	m_iErrorState = setBaudRate();
	if(m_iErrorState != 0)
		return m_iErrorState;

	m_iErrorState = clearReadQueue();
	if(m_iErrorState != 0)
		return m_iErrorState;

	if(m_iErrorState == 0)
		m_bInitFlag = true;

	updateModuleIdMap();
	return m_iErrorState;
}