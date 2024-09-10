uint32	CEditToolApp::GetEvent(unsigned uWaitTime) //原类型在CAynPipeReactor中
{
	const uint32 uResult=MsgWaitForMultipleObjectsEx((uint32)m_vecEvent.size(),&m_vecEvent[0],
		uWaitTime,QS_ALLINPUT, MWMO_ALERTABLE|MWMO_INPUTAVAILABLE );

	switch( uResult )
	{
	case WAIT_OBJECT_0:
		return eGER_Canceled;
	case WAIT_TIMEOUT:
		return eGER_TimedOut;
	case WAIT_IO_COMPLETION:
		return eGER_Iocp;
	case WAIT_FAILED:
		{
			ostringstream strm;
			strm<<"MsgWaitForMultipleObjectsEx failed";
			GenErr(strm.str());
		}
	default:
		{
			const uint32 uMsg=WAIT_OBJECT_0+m_vecEvent.size();
			if( uResult == uMsg  )
			{
				return eGER_SysMsg;
			}
			else if (uResult < uMsg || uResult > WAIT_OBJECT_0)
			{
				return eGER_NetMsg;
			}
			else
			{
				GenErr("MsgWaitForMultipleObjectsEx return invalid result.");
			}
		}
	}

	return eGER_NetMsg;
}