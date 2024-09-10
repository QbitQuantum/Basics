void CTCPConnection::Process (void)
{
	if (m_bTimedOut)
	{
		m_nErrno = -1;
		NEW_STATE (TCPStateClosed);
		m_Event.Set ();
		return;
	}

	switch (m_State)
	{
	case TCPStateClosed:
	case TCPStateListen:
	case TCPStateFinWait2:
	case TCPStateTimeWait:
		return;

	case TCPStateSynSent:
	case TCPStateSynReceived:
		if (m_bSendSYN)
		{
			m_bSendSYN = FALSE;
			if (m_State == TCPStateSynSent)
			{
				SendSegment (TCP_FLAG_SYN, m_nISS);
			}
			else
			{
				SendSegment (TCP_FLAG_SYN | TCP_FLAG_ACK, m_nISS, m_nRCV_NXT);
			}
			m_RTOCalculator.SegmentSent (m_nISS);
			StartTimer (TCPTimerRetransmission, m_RTOCalculator.GetRTO ());
		}
		return;
		
	case TCPStateEstablished:
	case TCPStateFinWait1:
	case TCPStateCloseWait:
	case TCPStateClosing:
	case TCPStateLastAck:
		if (   m_RetransmissionQueue.IsEmpty ()
		    && m_TxQueue.IsEmpty ()
		    && m_bFINQueued)
		{
			SendSegment (TCP_FLAG_FIN | TCP_FLAG_ACK, m_nSND_NXT, m_nRCV_NXT);
			m_RTOCalculator.SegmentSent (m_nSND_NXT);
			m_nSND_NXT++;
			NEW_STATE (m_StateAfterFIN);
			m_bFINQueued = FALSE;
			StartTimer (TCPTimerRetransmission, m_RTOCalculator.GetRTO ());
		}
		break;
	}

	assert (m_pTempBuffer != 0);
	unsigned nLength;
	while (    m_RetransmissionQueue.GetFreeSpace () >= FRAME_BUFFER_SIZE
		&& (nLength = m_TxQueue.Dequeue (m_pTempBuffer)) > 0)
	{
#ifdef TCP_DEBUG
		CLogger::Get ()->Write (FromTCP, LogDebug, "Transfering %u bytes into RT buffer", nLength);
#endif

		m_RetransmissionQueue.Write (m_pTempBuffer, nLength);
	}

	if (m_bRetransmit)
	{
#ifdef TCP_DEBUG
		CLogger::Get ()->Write (FromTCP, LogDebug, "Retransmission (nxt %u, una %u)", m_nSND_NXT-m_nISS, m_nSND_UNA-m_nISS);
#endif
		m_bRetransmit = FALSE;
		m_RetransmissionQueue.Reset ();
		m_nSND_NXT = m_nSND_UNA;
	}

	u32 nBytesAvail;
	u32 nWindowLeft;
	while (   (nBytesAvail = m_RetransmissionQueue.GetBytesAvailable ()) > 0
	       && (nWindowLeft = m_nSND_UNA+m_nSND_WND-m_nSND_NXT) > 0)
	{
		nLength = min (nBytesAvail, nWindowLeft);
		nLength = min (nLength, m_nSND_MSS);

#ifdef TCP_DEBUG
		CLogger::Get ()->Write (FromTCP, LogDebug, "Transfering %u bytes into TX buffer", nLength);
#endif

		assert (nLength <= FRAME_BUFFER_SIZE);
		m_RetransmissionQueue.Read (m_pTempBuffer, nLength);

		unsigned nFlags = TCP_FLAG_ACK;
		if (   m_RetransmissionQueue.IsEmpty ()
		    && m_TxQueue.IsEmpty ())
		{
			nFlags |= TCP_FLAG_PUSH;
		}

		SendSegment (nFlags, m_nSND_NXT, m_nRCV_NXT, m_pTempBuffer, nLength);
		m_RTOCalculator.SegmentSent (m_nSND_NXT, nLength);
		m_nSND_NXT += nLength;
		StartTimer (TCPTimerRetransmission, m_RTOCalculator.GetRTO ());
	}
}