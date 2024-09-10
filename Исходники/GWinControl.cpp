//-------------------------------------------------------------------------
//	redraw window
//-------------------------------------------------------------------------
void GWinControl::Refresh()
{
	if ( m_Hwnd)
	{
		//	invalidate whole window for redrawing
		if ( InvalidateRgn( m_Hwnd, NULL, TRUE ) )
		{
			UpdateWindow( m_Hwnd );
		}
		else
		{
			GDebug::CheckWin32Error();
		}
	}

	//	refresh is manually called, so update scrollbars
	UpdateScrollBars();
}