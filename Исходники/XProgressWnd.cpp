//=============================================================================
BOOL CXProgressWnd::DestroyWindow() 
//=============================================================================
{
	if (m_bPersistentPosition)
		SaveCurrentSettings();

	if (IsWindow(m_avi.m_hWnd))
	{
		m_avi.Stop();
		m_avi.Close();
	}

	if (m_bModal)
	{
		m_bModal = FALSE;

		if (m_wRenenableWnd && IsWindow(m_wRenenableWnd->m_hWnd))
			m_wRenenableWnd->EnableWindow(TRUE);
	}
	
	return CWnd::DestroyWindow();
}