void CSUIButton::CountDPI(){
	if(!nLogDPIX){
		CDC ScreenDC;
		ScreenDC.CreateIC(_T("DISPLAY"), NULL, NULL, NULL);
		nLogDPIX = ScreenDC.GetDeviceCaps(LOGPIXELSX), nLogDPIY = ScreenDC.GetDeviceCaps(LOGPIXELSY);
	}

	m_orgbtnSize = m_btnSize;

	m_btnSize.cx = nLogDPIX  * m_orgbtnSize.cx / 96;
	m_btnSize.cy = nLogDPIY * m_orgbtnSize.cy / 96;
}