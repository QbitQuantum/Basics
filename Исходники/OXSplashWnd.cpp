int COXSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
	{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if ((HRGN)m_rgn != NULL)
		{
		CRgn rgn;
		rgn.CreateRectRgn(0,0,1,1);
		switch(rgn.CopyRgn(&m_rgn))
			{
			case ERROR:
				TRACE0("COXSplashWnd::OnCreate(): fail to load the calculated region.\r\n");
				rgn.DeleteObject();
				break;
			case NULLREGION:
				TRACE0("COXSplashWnd::OnCreate(): empty region was encountered.\r\n");
				rgn.DeleteObject();
				break;
			default:
				::SetWindowRgn(m_hWnd, (HRGN)rgn.Detach(), TRUE);
			}
		}
	
	CenterWindow();
	if (m_nTimeout != SPLASH_NOTIMER)
		SetTimer(OXSPLASHWND_TIMERID_HIDE, m_nTimeout, NULL);

	SetCapture();
	::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	return 0;
	}