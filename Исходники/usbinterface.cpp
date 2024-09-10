void UsbInterfacePrivate::threadFunc()
{
	HANDLE handles[1+m_oCount];
	handles[0] = m_quitEvent;
	handles[m_oCount] = m_waitEvents[m_oCount-1];
	//= { m_quitEvent, m_waitEvents[0], m_waitEvents[1] };

	// start first read operation
	for (m_readIdx = 0 ; m_readIdx < (m_oCount-1); ++m_readIdx)
	{
		handles[m_readIdx+1] = m_waitEvents[m_readIdx];
		//m_readIdx = 0;
		m_overlapped[m_readIdx] = OVERLAPPED();
		::ResetEvent(m_waitEvents[m_readIdx]);		//lint !e534
		m_overlapped[m_readIdx].hEvent = m_waitEvents[m_readIdx];
		WinUsb_ReadPipe(m_usbHandle[1],
			m_bulkInPipe,
			m_fixedBuffer[m_readIdx],
			(ULONG)m_fixedBufferSize,
			0,
			&m_overlapped[m_readIdx]);	//lint !e534
	}
	int fastCount = 0;
	//m_readIdx = 1;
	bool policyFast = false;
	bool run = true;
	while (run)
	{
		// start follow-up read operation
		m_overlapped[m_readIdx] = OVERLAPPED();
		::ResetEvent(m_waitEvents[m_readIdx]);		//lint !e534
		m_overlapped[m_readIdx].hEvent = m_waitEvents[m_readIdx];
		WinUsb_ReadPipe(m_usbHandle[1],
			m_bulkInPipe,
			m_fixedBuffer[m_readIdx],
			(ULONG)m_fixedBufferSize,
			0,
			&m_overlapped[m_readIdx]);	//lint !e534
		m_readIdx = (m_readIdx + 1) % m_oCount;
		int64_t tBegin = XsTime_timeStampNow(0);
		DWORD waitResult = ::WaitForMultipleObjects(1+m_oCount, handles, FALSE, INFINITE);
#if 1	// not sure if this causes problems, but it should help in catching up
		int64_t tEnd = XsTime_timeStampNow(0);
		switch (tEnd - tBegin)
		{
		case 0:
			if (++fastCount > 3 && !policyFast)
			{
				policyFast = true;
				// set fast policy
				UCHAR enable = TRUE;
				WinUsb_SetPipePolicy(m_usbHandle[1], m_bulkInPipe, IGNORE_SHORT_PACKETS, sizeof(UCHAR), &enable);	//lint !e534
			}
			break;

		case 1:
			if (fastCount)
				--fastCount;
			if (policyFast && fastCount <= 3)
			{
				// reset policy
				policyFast = false;
				UCHAR enable = FALSE;
				WinUsb_SetPipePolicy(m_usbHandle[1], m_bulkInPipe, IGNORE_SHORT_PACKETS, sizeof(UCHAR), &enable);	//lint !e534
			}
			break;

		default:
			fastCount = 0;
			if (policyFast)
			{
				// reset policy
				policyFast = false;
				UCHAR enable = FALSE;
				WinUsb_SetPipePolicy(m_usbHandle[1], m_bulkInPipe, IGNORE_SHORT_PACKETS, sizeof(UCHAR), &enable);	//lint !e534
			}
			break;
		}
#endif

		// handle data
		switch (waitResult)
		{
		case WAIT_TIMEOUT:
		case WAIT_FAILED:
		case WAIT_OBJECT_0:
			run = false;
			break;

		default:
			if (waitResult >= WAIT_ABANDONED_0)
			{
				JLDEBUG(gJournal, "WFMO abandoned: " << (waitResult - WAIT_OBJECT_0));
				break;
			}

#ifndef XSENS_RELEASE
			JLDEBUG(gJournal, "WFMO trigger: " << (waitResult - WAIT_OBJECT_0));
#endif
			{
				// put data into buffer
				int idx = m_readIdx;
				DWORD dataRead = 0;
				if (!WinUsb_GetOverlappedResult(m_usbHandle[0], &m_overlapped[idx], &dataRead, FALSE))
				{
					// error
					DWORD err = ::GetLastError();
					switch (err)
					{
					case ERROR_SEM_TIMEOUT:
					case ERROR_IO_INCOMPLETE:
						//JLDEBUG(gJournal, "WinUsb_GetOverlappedResult resulted in acceptable windows error " << err);
						break;

					default:
						JLALERT(gJournal, "WinUsb_GetOverlappedResult resulted in windows error " << err);
						run = false;
						break;
					}
					//assert (err == ERROR_IO_INCOMPLETE);
				}
				else
				{
					// append unread data to var buffer
					JLTRACE(gJournal, "WinUsb_GetOverlappedResult resulted in " << dataRead << " bytes being read");
					XsByteArray ref(&m_fixedBuffer[idx][0], dataRead, XSDF_None);
					::EnterCriticalSection(&m_mutex);
					m_varBuffer.append(ref);
					::LeaveCriticalSection(&m_mutex);
				}
			} break;
		}
	}
}