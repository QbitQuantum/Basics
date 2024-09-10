bool CApoxObj::open( const char *szFileName, unsigned long flags )
{
	const char *p;
	unsigned long busspeed = 125;
	m_emergencyInfo = 0;
	char szDrvParams[ MAX_PATH ];
	m_initFlag = flags;

	m_RxMsgState = USB_IDLE;

	// save parameter string and conbert to upper case
	strncpy( szDrvParams, szFileName, MAX_PATH );
	_strupr( szDrvParams );

	// Initiate statistics
	m_stat.cntReceiveData = 0;
	m_stat.cntReceiveFrames = 0;
	m_stat.cntTransmitData = 0;
	m_stat.cntTransmitFrames = 0;

	m_stat.cntBusOff = 0;
	m_stat.cntBusWarnings = 0;
	m_stat.cntOverruns = 0;

	// if open we have noting to do
	if ( m_bRun ) return true;
		
	// serial
	p = strtok( szDrvParams, ";" );
	if ( NULL != p ) {		
		strcpy( m_SerialNumber, p );	
	}

	// Bus-Speed
	p = strtok( NULL, ";" );
	if ( NULL != p ) {		
		if ( ( NULL != strstr( p, "0x" ) ) || ( NULL != strstr( p, "0X" ) )  ) {
			sscanf( p + 2, "%x", &busspeed );
		}
		else {
			busspeed = atol( p );
		}
	}

	// Handle busspeed
	uint8_t nSpeed = CAN_BAUD_1000;
	switch ( busspeed ) {

		case 125:
			nSpeed = CAN_BAUD_125;
			break;

		case 250:
			nSpeed = CAN_BAUD_250;
			break;

		case 500:
			nSpeed = CAN_BAUD_500;
			break;

		case 1000:
			nSpeed = CAN_BAUD_1000;
			break;

		default:
			nSpeed = CAN_BAUD_125;
			break;

	}


	FT_STATUS ftStatus;
	ftStatus = FT_OpenEx( (void *)m_SerialNumber, 
							FT_OPEN_BY_SERIAL_NUMBER, 
							&m_ftHandle );
	if ( !FT_SUCCESS( ftStatus ) ) return false;
		
	ftStatus = FT_ResetDevice( m_ftHandle );
	ftStatus = FT_Purge( m_ftHandle, FT_PURGE_RX | FT_PURGE_TX );
	ftStatus = FT_SetTimeouts(m_ftHandle, 378, 128);
	ftStatus = FT_SetUSBParameters ( m_ftHandle, 2048, 2048 );
	ftStatus = FT_SetLatencyTimer( m_ftHandle, 3 );
    
	
	// Run run run ..... 

	m_bRun = true;

#ifdef WIN32
	
	// Start write thread 
	DWORD threadId;
	if ( NULL == 
			( m_hTreadTransmit = CreateThread(	NULL,
										0,
										(LPTHREAD_START_ROUTINE) workThreadTransmit,
										this,
										0,
										&threadId ) ) ) { 
		// Failure
		close();
		return false;
	}

	// Start read thread 
	if ( NULL == 
			( m_hTreadReceive = CreateThread(	NULL,
										0,
										(LPTHREAD_START_ROUTINE) workThreadReceive,
										this,
										0,
										&threadId ) ) ) { 
		// Failure
		close();
		return  false;
	}
	
	// Release the mutex
	UNLOCK_MUTEX( m_apoxMutex );
	UNLOCK_MUTEX( m_receiveMutex );
	UNLOCK_MUTEX( m_transmitMutex );
	UNLOCK_MUTEX( m_responseMutex );

#else // LINUX


	pthread_attr_t thread_attr;
	pthread_attr_init( &thread_attr );
	
	
	// Create the log write thread.
	if ( pthread_create( 	&m_threadId,
								&thread_attr,
								workThreadTransmit,
								this ) ) {	
							
		syslog( LOG_CRIT, "canallogger: Unable to create apoxdrv write thread.");
		rv = false;
		fclose( m_flog );
	}


	// Create the log write thread.
	if ( pthread_create( 	&m_threadId,
								&thread_attr,
								workThreadReceive,
								this ) ) {	
							
		syslog( LOG_CRIT, "canallogger: Unable to create apoxdrv receive thread.");
		rv = false;
		fclose( m_flog );
	}
		
    // We are open
	m_bOpen = true;

	// Release the mutex
	pthread_mutex_unlock( &m_apoxMutex );

#endif	

	// Switch to main mode if in boot mode
	if ( RUNMODE_BOOT == getAdapterRunMode() ) {
		setAdapterRunMode( RUNMODE_MAIN );
	}

	// Set baudrate
	setBaudrate( nSpeed );

	// Set initial filter/mask	
	switch( m_initFlag & 0x03 ) {

		case 0:
		case 3:
			m_filtermask.rx_buff1_ext = 0;
			m_filtermask.rx_buff2_ext = 1;
			break;

		case 1:
			m_filtermask.rx_buff1_ext = 0;
			m_filtermask.rx_buff2_ext = 0;
			break;

		case 2:
			m_filtermask.rx_buff1_ext = 1;
			m_filtermask.rx_buff2_ext = 1;
			break;
	}

	m_filtermask.RXM0 = 0;
	m_filtermask.RXM1 = 0;
	m_filtermask.RXF0 = 0;	
	m_filtermask.RXF1 = 0;
	m_filtermask.RXF2 = 0;
	m_filtermask.RXF3 = 0;
	m_filtermask.RXF4 = 0;
	m_filtermask.RXF5 = 0;

	setAdapterFilterMask( &m_filtermask );

	// Set transmission mode
	short trmode = ( (short)( m_initFlag & 0x0c ) >> 2 );
	if ( 0 == trmode ) trmode = TRMODE_NORMAL;
	setTransmissionMode( trmode );

	return true;
}