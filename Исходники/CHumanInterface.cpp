DWORD CHumanInterface::AddTimer (DWORD dwMilliseconds, IHICommand *pListener, const CString &sCmd, bool bRecurring)

//	AddTimer
//
//	Adds a timer

	{
	return m_Timers.AddTimer(m_hWnd,
			dwMilliseconds,
			(pListener ? pListener : m_pController),
			(!sCmd.IsBlank() ? sCmd : CONSTLIT("cmdTimer")),
			bRecurring);
	}