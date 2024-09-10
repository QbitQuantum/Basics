BOOL COpenDesktop::_CloseDesktop()
{
	if (!SetProcessWindowStation(m_hwinstaCurrent))
		return FALSE;
	
	if (!SetThreadDesktop(m_hdeskCurrent))
		return FALSE;
	
	if (!CloseWindowStation(m_hwinsta))
		return FALSE;
	
	if (!CloseDesktop(m_hdesk))
		return FALSE;
	
	return TRUE;
}