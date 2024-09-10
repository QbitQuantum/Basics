void CPic_Earth::InitCheck()
{
	CRect chkRect;

	chkRect.SetRect(262, 170, 306, 190);
	m_gpCheck.Create( "GPS", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,  
                   chkRect, this, 1023);  
	m_gpCheck.SetCheck(1);

	chkRect.SetRect(236, 190, 306, 210);
	m_glCheck.Create( "Glonass", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,  
                   chkRect, this, 1024); 
	m_glCheck.SetCheck(1);

	chkRect.SetRect(244, 210, 306, 230);
	m_bdCheck.Create( "Beidou", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,  
                   chkRect, this, 1025);  
	m_bdCheck.SetCheck(1);

	chkRect.SetRect(244, 230, 306, 250);
	m_gaCheck.Create( "Galileo", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,  
                  chkRect, this, 1026);  
	m_gaCheck.SetCheck(1);
}