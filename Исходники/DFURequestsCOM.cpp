// Automatic protocol detection
DFUEngine::Result DFURequestsCOM::AutomaticPassiveBCSP()
{
	// Ensure that any previous transport is disconnected
	impl_->transport.Disconnect();

	// Purge any operations in progress
	if (!PurgeComm(impl_->com, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
	{
		return DFUEngine::fail_os;
	}

	// Read the current COM port settings
	DCB dcb;
	COMMTIMEOUTS timeouts;
	if (!GetCommState(impl_->com, &dcb) || !GetCommTimeouts(impl_->com, &timeouts))
	{
		return DFUEngine::fail_os;
	}
	
	// Set the basic COM port configuration
	dcb.fBinary = true;
	dcb.fParity = comParity != NOPARITY;
	dcb.fOutxCtsFlow = true;
	dcb.fOutxDsrFlow = false;
	dcb.fDsrSensitivity = false;
	dcb.fOutX = false;
	dcb.fInX = false;
	dcb.fErrorChar = false;
	dcb.fNull = false;
	dcb.fAbortOnError = false;
	dcb.ByteSize = comDataBits;
	dcb.Parity = comParity;
	dcb.StopBits = comStopBits;
	if (!SetCommState(impl_->com, &dcb))
	{
		return DFUEngine::fail_os;
	}

	// Set the timeouts for reading
	uint32 timeout = impl_->baud && impl_->baud->next
		             ? comReceiveMilliseconds
					 : comReceiveMillisecondsSingle;
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutConstant = timeout;
	timeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
	if (!SetCommTimeouts(impl_->com, &timeouts))
	{
		return DFUEngine::fail_os;
	}

	// Attempt to reset the connection using the handshaking lines
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	if (!SetCommState(impl_->com, &dcb))
	{
		return DFUEngine::fail_os;
	}
	Sleep(comHandshakeMilliseconds);
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	if (!SetCommState(impl_->com, &dcb))
	{
		return DFUEngine::fail_os;
	}

	// Loop through each of the baud rates
	int bufferLength = 2 * sizeof(bcspSync);
	SmartPtr<uint8, true> buffer(new uint8[bufferLength]);
	bool connected = false;
	for (BaudRateList *pos = impl_->baud;
	     !connected && pos; pos = pos->next)
	{
		// Check for an abort request
		DFUEngine::Result result = CheckAbort();
		if (!result) return result;

		// Configure the port for this baud rate
		int baudRate = pos->baud;
		Progress(DFUEngine::transport_bcsp_passive_le, baudRate);
		dcb.BaudRate = baudRate;
		if (!SetCommState(impl_->com, &dcb))
		{
			return DFUEngine::fail_os;
		}

		// Look for the BCSP sync message
		int bufferUsed = 0;
		uint32 endTick = GetTickCount() + timeout;
		while (!connected && (int32(GetTickCount() - endTick) < 0))
		{
			// Ensure that there is sufficient space in the buffer
			DWORD read;
			int bufferLeave = sizeof(bcspSync) - 1;
			if (bufferLeave < bufferUsed)
			{
				// Shuffle the existing contents down
				memmove(buffer, buffer + bufferUsed - bufferLeave,
				        bufferLeave);
				bufferUsed = bufferLeave;
			}

			// Read some more data from the serial port
#if !defined _WINCE && !defined _WIN32_WCE
			OVERLAPPED overlapped;
			overlapped.Offset = 0;
			overlapped.OffsetHigh = 0;
			HANDLE event = CreateEvent(NULL, TRUE, FALSE, NULL);
			if(!event) return DFUEngine::fail_os;

			overlapped.hEvent = event;
			if (!ReadFile(impl_->com, buffer + bufferUsed,
			              bufferLength - bufferUsed, &read, &overlapped)
				&& (GetLastError() != ERROR_IO_PENDING))
			{
				CloseHandle(event);
				return DFUEngine::fail_os;
			}

			// Wait for the operation to complete
			WaitForSingleObject(event, timeout);
			CloseHandle(event);

			// Get the result
			if (!GetOverlappedResult(impl_->com, &overlapped, &read, false))
			{
				return DFUEngine::fail_os;
			}
#else
			// Set the serial port timeouts to return immediately
			COMMTIMEOUTS timeouts;
			memset(&timeouts, 0, sizeof(timeouts));
			timeouts.ReadIntervalTimeout = MAXDWORD;
			timeouts.ReadTotalTimeoutConstant = 0;
			timeouts.ReadTotalTimeoutMultiplier = 0;
			timeouts.WriteTotalTimeoutMultiplier = 0;
			timeouts.WriteTotalTimeoutConstant = 0;
			if (!SetCommTimeouts(impl_->com, &timeouts))
			{
				return DFUEngine::fail_os;
			}

			// Read any waiting data
			if (!ReadFile(impl_->com, buffer + bufferUsed,
				bufferLength - bufferUsed, &read, 0))
			{
				return DFUEngine::fail_os;
			}
#endif

			// Update the buffer position
			bufferUsed += read;

			// Check if the BCSP sync message has been received
			for (int offset = 0;
			     !connected && (offset + int(sizeof(bcspSync)) <= bufferUsed);
				 ++offset)
			{
				connected = !memcmp(buffer + offset,
				                    bcspSync, sizeof(bcspSync));
			}
		}

		// Store the baud rate and link establishment if successful
		if (connected)
		{
			FreeBaudRateList(impl_->baud);
			impl_->baud = new BaudRateList;
			impl_->baud->next = 0;
			impl_->baud->baud = baudRate;

			impl_->sync = sync_enabled;
		}
	}

	// Return an error if failed to connect
	if (!connected) return DFUEngine::fail_com_connect;

	// Attempt to start the actual transport
	DFUEngine::Result result = impl_->transport.ConnectBCSP(impl_->port, impl_->baud->baud, true, false, impl_->com);
	if (!result) return result;

	// Check if private channels work
	result = TestPrivateChannel();
	if (!result)
	{
		// Try tunnelling if appropriate
		if ((impl_->protocol == protocol_unknown)
			|| (impl_->protocol == protocol_bcsp_tunnel))
		{
			// Try again with tunnelling
            result = impl_->transport.ConnectBCSP(impl_->port, impl_->baud->baud, true, true, impl_->com);
            if (result)
                result = TestPrivateChannel();
			if (!result) return result;

			// Store the protocol if successful
			impl_->protocol = protocol_bcsp_tunnel;
		}
		else return result;
	}

	// Successful if this point reached
	return DFUEngine::success;
}