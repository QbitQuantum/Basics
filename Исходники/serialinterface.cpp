/*! \brief Open a communication channel to the given port info.
	\details If the baudrate in \a portInfo is set to XBR_Invalid, the baud rate is automatically
				detected if possible.
	\param portInfo The details of the port that should be opened. Depending on the type of interface,
				parts of this parameter may be ignored.
	\param readBufSize The size of the read buffer in bytes (if appliccable to the device)
	\param writeBufSize The size of the write buffer in bytes (if appliccable to the device)
	\param options The options to enable (flow control, stop bits)
	\returns XRV_OK if the device was opened successfully
*/
XsResultValue SerialInterface::open(const XsPortInfo& portInfo,
						uint32_t readBufSize,
						uint32_t writeBufSize,
						PortOptions options)
{
	m_endTime = 0;

	JLDEBUG(gJournal, portInfo);

	if (isOpen())
	{
		JLALERT(gJournal, "Port " << portInfo.portName() << " is already open");
		return (m_lastResult = XRV_ALREADYOPEN);
	}
	m_baudrate = portInfo.baudrate();

	if (options&PO_RtsCtsFlowControl)
		JLTRACE(gJournal, "Requested RTS/CTS flow control");
	if (options&PO_DtrDsrFlowControl)
		JLTRACE(gJournal, "Requested DTR/DSR flow control");
	if (options&PO_XonXoffFlowControl)
		JLTRACE(gJournal, "Requested Xon/Xoff flow control");

#ifdef _WIN32
	XsResultValue fail = XRV_OK;
	char winPortName[256];

	// Open port
	sprintf(winPortName, "\\\\.\\%s", portInfo.portName().c_str());
	m_handle = CreateFileA(winPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL,
									OPEN_EXISTING, 0, NULL);
	if (m_handle == INVALID_HANDLE_VALUE)
	{
		JLDEBUG(gJournal, "Port " << portInfo.portName() << " cannot be opened");
		return (m_lastResult = XRV_INPUTCANNOTBEOPENED);
	}

	DCB commState;		//!< Stored settings about the serial port

	commState.DCBlength = sizeof(DCB);

	//Get the current state & then change it
	if (!GetCommState(m_handle, &commState))	// Get current state
		fail = XRV_ERROR;

	commState.BaudRate = (int) portInfo.baudrate();		// Setup the baud rate
	commState.Parity = NOPARITY;				// Setup the Parity
	commState.ByteSize = 8;					// Setup the data bits
	commState.StopBits = (options&PO_TwoStopBits)?TWOSTOPBITS:ONESTOPBIT;

	// Setup flow control
	commState.fDsrSensitivity = (options&PO_DtrDsrFlowControl)?TRUE:FALSE;
	commState.fOutxDsrFlow = (options&PO_DtrDsrFlowControl)?DTR_CONTROL_HANDSHAKE:DTR_CONTROL_DISABLE;

	commState.fOutxCtsFlow = (options&PO_RtsCtsFlowControl)?TRUE:FALSE;
	commState.fRtsControl = (options&PO_RtsCtsFlowControl)?RTS_CONTROL_HANDSHAKE:RTS_CONTROL_ENABLE;

	commState.fOutX = (options&PO_XonXoffFlowControl)?TRUE:FALSE;
	commState.fInX = commState.fOutX;

	if (!SetCommState(m_handle, (LPDCB)&commState)) // Set new state
	{
		// Bluetooth ports cannot always be opened with 2 stopbits
		// Now try to open port with 1 stopbit.
		commState.StopBits = ONESTOPBIT;
		if (!SetCommState(m_handle, (LPDCB)&commState))
			fail = XRV_INPUTCANNOTBEOPENED;
	}
	std::string tmp = portInfo.portName().toStdString();
	m_port = atoi(&tmp.c_str()[3]);
	sprintf(m_portname, "%s", tmp.c_str());

	if (setTimeout(20))
		fail = m_lastResult;

	// Other initialization functions
	if ((options&PO_DtrDsrFlowControl) == 0)
	{
		if (!EscapeCommFunction(m_handle, SETDTR))			// Set DTR (Calibration sensors need DTR to startup, won't hurt otherwise
			fail = XRV_ERROR;
	}
	if (!SetupComm(m_handle,readBufSize,writeBufSize))	// Set queue size
		fail = XRV_ERROR;

	// Remove any 'old' data in buffer
	//PurgeComm(m_handle, PURGE_TXCLEAR | PURGE_RXCLEAR);
	if (!PurgeComm(m_handle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
		fail = XRV_ERROR;

	if (fail != XRV_OK)
	{
		CloseHandle(m_handle);		//lint !e534
		m_handle = INVALID_HANDLE_VALUE;
		return (m_lastResult = fail);
	}

#else // !_WIN32
	(void)readBufSize;
	(void)writeBufSize;
	// Open port
	std::string pn = portInfo.portName().toStdString();
	m_handle = ::open(pn.c_str(), O_RDWR | O_NOCTTY);

	// O_RDWR: Read+Write
	// O_NOCTTY: Raw input, no "controlling terminal"
	// O_NDELAY: Don't care about DCD signal

	if (m_handle < 0) {
		// Port not open
		return m_lastResult = XRV_INPUTCANNOTBEOPENED;
	}

	// Check if the file is already opened by someome else (other thread/process)
	if (flock(m_handle, LOCK_EX | LOCK_NB))
	{
		closeLive();
		return m_lastResult = XRV_INPUTCANNOTBEOPENED;
	}

	/* Start configuring of port for non-canonical transfer mode */
	// Get current options for the port
	if (tcgetattr(m_handle, &m_commState) != 0)
		return XRV_ERROR;

	// Set baudrate.
	if (cfsetispeed(&m_commState, portInfo.baudrate()) != 0)
		return XRV_ERROR;

	if (cfsetospeed(&m_commState, portInfo.baudrate()) != 0)
		return XRV_ERROR;

	// Enable the receiver and set local mode
	m_commState.c_cflag |= (CLOCAL | CREAD);
	// Set character size to data bits and set no parity Mask the characte size bits
	m_commState.c_cflag &= ~(CSIZE|PARENB|PARODD);
	m_commState.c_cflag |= CS8;		// Select 8 data bits

	m_commState.c_cflag = setBitsEnabled(m_commState.c_cflag, (tcflag_t)CSTOPB, (options&PO_TwoStopBits) == PO_TwoStopBits);

	// Hardware flow control
	m_commState.c_cflag = setBitsEnabled(m_commState.c_cflag, (tcflag_t)CRTSCTS, (options&PO_RtsCtsFlowControl) == PO_RtsCtsFlowControl);
#ifdef CDTRDSR
	m_commState.c_cflag = setBitsEnabled(m_commState.c_cflag, (tcflag_t)CDTRDSR, (options&PO_DtrDsrFlowControl) == PO_DtrDsrFlowControl);
#endif

	m_commState.c_lflag &= ~(ECHO|ECHOE|ECHOK|ECHONL|ICANON|ISIG|IEXTEN);
	// Software flow control
	m_commState.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|INPCK|ISTRIP|INLCR|IGNCR|ICRNL);
	m_commState.c_iflag = setBitsEnabled(m_commState.c_iflag, (tcflag_t)(IXON|IXOFF), options&PO_XonXoffFlowControl);
	// Set Raw output
	m_commState.c_oflag &= ~OPOST;
	// Timeout 0.001 sec for first byte, read minimum of 0 bytes
	m_commState.c_cc[VMIN]     = 0;
	m_commState.c_cc[VTIME]    = (m_timeout+99)/100;	// 1

	// Set the new options for the port
	if (tcsetattr(m_handle,TCSANOW, &m_commState) != 0)
		return XRV_INPUTCANNOTBEOPENED;

#if defined(JLLOGLEVEL) && JLLOGLEVEL <= JLL_ALERT
	termios checkCommState;
	if (tcgetattr(m_handle, &checkCommState) != 0)
		return XRV_ERROR;

	if (cfgetispeed(&checkCommState) != portInfo.baudrate())
		JLALERT(gJournal, "Set baudrate doesn't match requested baudrate");

	if (cfgetospeed(&checkCommState) != portInfo.baudrate())
		JLALERT(gJournal, "Set baudrate doesn't match requested baudrate");

	if (options&PO_RtsCtsFlowControl && !(checkCommState.c_cflag&CRTSCTS))
		JLALERT(gJournal, "Requested RTS/CTS flow control, but could not be set.");

	if (options&PO_DtrDsrFlowControl &&
#ifdef CDTRDSR
		!(checkCommState.c_cflag&CDTRDSR)
#else
		false
#endif
		)
		JLALERT(gJournal, "Requested DTR/DSR flow control, but could not be set.");

	if (options&PO_XonXoffFlowControl && !((checkCommState.c_iflag&(IXON|IXOFF)) == (IXON|IXOFF)))
		JLALERT(gJournal, "Requested Xon/Xoff flow control, but could not be set.");
#endif // JLLOGLEVEL < JLL_ALERT

#if defined(JLLOGLEVEL) && JLLOGLEVEL <= JLL_DEBUG
#define CHECK_COMMSTATE(req, res, field)\
	if (req.field != res.field) \
	{\
		JLDEBUG(gJournal, "field " << #field << " does not match");\
		JLDEBUG(gJournal, "actual  : " << std::oct << (uint64_t)res.field);\
		JLDEBUG(gJournal, "expected: " << std::oct << (uint64_t)req.field);\
	}
#else
#define CHECK_COMMSTATE(req, res, field)
#endif
	CHECK_COMMSTATE(m_commState, checkCommState, c_cflag);
	CHECK_COMMSTATE(m_commState, checkCommState, c_iflag);
	CHECK_COMMSTATE(m_commState, checkCommState, c_oflag);
	CHECK_COMMSTATE(m_commState, checkCommState, c_cc[VMIN]);
	CHECK_COMMSTATE(m_commState, checkCommState, c_cc[VTIME]);

	m_port = 1;
	sprintf(m_portname, "%s", pn.c_str());

	tcflush(m_handle, TCIOFLUSH);

	// setting RTS and DTR; RTS for Xbus Master, DTR for calibration sensors
	int cmbits;
	if (ioctl(m_handle, TIOCMGET, &cmbits) < 0)
	{
		JLDEBUG(gJournal, "TIOCMGET failed, which is OK for USB connected MkIV devices");
	}

	if ((options&PO_RtsCtsFlowControl) == 0)
		cmbits = setBitsEnabled(cmbits, TIOCM_RTS, true);
	// else don't touch them

	cmbits = setBitsEnabled(cmbits, TIOCM_DTR, !(options&PO_DtrDsrFlowControl));

	if (ioctl(m_handle, TIOCMSET, &cmbits) < 0)
	{
		JLDEBUG(gJournal, "TIOCMSET failed, which is OK for USB connected MkIV devices");
	}
#endif // !_WIN32

	JLDEBUG(gJournal, "Port " << portInfo.portName().toStdString() << " opened");
	return (m_lastResult = XRV_OK);
}