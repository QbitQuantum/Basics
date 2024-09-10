void SUIVoteStar::CountDPI(){
	if(!nLogDPIX){
		CDC ScreenDC;
		ScreenDC.CreateIC(_T("DISPLAY"), NULL, NULL, NULL);
		nLogDPIX = ScreenDC.GetDeviceCaps(LOGPIXELSX), nLogDPIY = ScreenDC.GetDeviceCaps(LOGPIXELSY);
	}

	m_StarBmpYellowSizeOrg = m_StarBmpYellowSize;
	m_StarBmpYellowSize.cx = nLogDPIX  * m_StarBmpYellowSizeOrg.cx / 96;
	m_StarBmpYellowSize.cy = nLogDPIY * m_StarBmpYellowSizeOrg.cy / 96;

	m_StarBmpNullSizeOrg = m_StarBmpNullSize;
	m_StarBmpNullSize.cx = nLogDPIX  * m_StarBmpNullSizeOrg.cx / 96;
	m_StarBmpNullSize.cy = nLogDPIY * m_StarBmpNullSizeOrg.cy / 96;

	m_StarBmpRedSizeOrg = m_StarBmpRedSize;
	m_StarBmpRedSize.cx = nLogDPIX  * m_StarBmpRedSizeOrg.cx / 96;
	m_StarBmpRedSize.cy = nLogDPIY * m_StarBmpRedSizeOrg.cy / 96;
}