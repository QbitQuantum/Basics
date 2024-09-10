bool cmtScanPort(CmtPortInfo& portInfo, uint32_t baud, uint32_t singleScanTimeout, uint32_t scanTries)
{
	uint32_t baudrate;
	Cmt3 port;
	port.setGotoConfigTries(scanTries?(uint16_t)scanTries:1);
	port.setTimeoutConfig(singleScanTimeout);
	XsensResultValue res;

	if (baud == 0)
		baudrate = CMT_BAUD_RATE_115K2;
	else
		baudrate = baud;

	while(!abortScan)
	{
		// try to connect at current baudrate
#ifdef _WIN32
		if ((res = port.openPort(portInfo.m_portNr,baudrate)) == XRV_OK)
#else
		if ((res = port.openPort(portInfo.m_portName,baudrate)) == XRV_OK)
#endif
		{
			SCANLOG("SP: L3 port-check returns OK\n");
			portInfo.m_baudrate = baudrate;
			portInfo.m_deviceId = port.getMasterId();
			return true;	// this also closes the port
		}
		// failed, determine if we need to scan other baudrates or not
		if (res != XRV_TIMEOUT && res != XRV_TIMEOUTNODATA && res != XRV_CONFIGCHECKFAIL)
		{
			SCANLOG("SP: L3 port-check returned ERROR, aborting\n");
			return false;
		}

		SCANLOG("SP: L3 port-check returned TIMEOUT, check next baudrate or abort\n");
		// not detected, try next baudrate
		if (baud != 0)
			return false;
		switch(baudrate)
		{
		default:
		case CMT_BAUD_RATE_115K2:
			baudrate = CMT_BAUD_RATE_460K8; break;
		case CMT_BAUD_RATE_460K8:
			baudrate = CMT_BAUD_RATE_921K6; break;
		case CMT_BAUD_RATE_921K6:
			baudrate = CMT_BAUD_RATE_230K4; break;
		case CMT_BAUD_RATE_230K4:
			baudrate = CMT_BAUD_RATE_57K6; break;
		case CMT_BAUD_RATE_57K6:
			baudrate = CMT_BAUD_RATE_38K4; break;
		case CMT_BAUD_RATE_38K4:
			baudrate = CMT_BAUD_RATE_19K2; break;
		case CMT_BAUD_RATE_19K2:
			baudrate = CMT_BAUD_RATE_9600; break;
		case CMT_BAUD_RATE_9600:
			return false;	// could not detect Xsens sensor, return false
		}
	}
	return false;
}