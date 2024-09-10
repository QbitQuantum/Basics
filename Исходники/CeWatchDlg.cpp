BOOL CCeWatchDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (pWnd != NULL && IsWindow(m_ToolTipCtrl.GetSafeHwnd()))	
	{
		POINT pt;
		CRect rc;
		::GetCursorPos(&pt);

		for (int ii = 0; ii < sizeof(m_ToolWndArray)/sizeof(CWnd*); ii++)
		{
			if (m_ToolWndArray[ii] != NULL && IsWindow(m_ToolWndArray[ii]->GetSafeHwnd()))
			{
				m_ToolWndArray[ii]->GetWindowRect(rc);
				if (rc.PtInRect(pt))
				{
					m_ToolWndArray[ii]->ScreenToClient(&pt);

					MSG msg;
					switch(message)
					{
					case WM_MOUSEMOVE:
					case WM_LBUTTONDOWN:
					case WM_MBUTTONDOWN:
					case WM_RBUTTONDOWN:
					case WM_LBUTTONUP:
					case WM_MBUTTONUP:
					case WM_RBUTTONUP:
						msg.message = message;            
						break;
					default:
						msg.message = WM_MOUSEMOVE;            					
						break;
					}
					msg.hwnd    = m_ToolWndArray[ii]->m_hWnd;
					msg.wParam  = 0;
					msg.lParam  = MAKELPARAM(pt.x, pt.y);     
					msg.time    = 0;
					msg.pt      = pt;
					m_ToolTipCtrl.RelayEvent(&msg);
					break;
				}
			}
		}
	}
	
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}