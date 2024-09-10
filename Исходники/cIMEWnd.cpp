void cIMEWnd::SetDockingEx(cIMEex * box, BOOL bDock )
{
	if( bDock )
	{
		m_pDockingEx = box;

		HWND curFocus = 0;
		curFocus = GetFocus();

		if(curFocus != _g_hWnd)
		{
			SetFocus(_g_hWnd);
			SetActiveWindow(_g_hWnd);
		}
	}
	else
	{
		if( box == m_pDockingEx )
			m_pDockingEx = NULL;
	}
}