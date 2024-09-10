ERTFToken RTFtime::Read (RTFParser& p)
{
//	<time>	\yr? \mo? \dy? \hr? \min? \sec?
	ERTFToken ec;
	for(;;)
	{
		ec = p.GetToken();
		if (ec == rtf_endgroup) 
		{
			p.PushToken(ec);
			return rtfec_OK;
		}

		switch(ec)
		{
		case rtfcw_yr : m_uiYear   = p.m_kw.param; continue;
		case rtfcw_mo : m_uiMonth  = p.m_kw.param; continue;
		case rtfcw_dy : m_uiDay    = p.m_kw.param; continue;
		case rtfcw_hr : m_uiHour   = p.m_kw.param; continue;
		case rtfcw_min: m_uiMinute = p.m_kw.param; continue;
		case rtfcw_sec: m_uiSecond = p.m_kw.param; continue;
		default:
			p.PushToken(ec);
			return rtfrc_NotMatched;
		}
	}
	THROW_FATAL_RTF_READERROR(false, _T("Reading Time"));
}