LONG CMCIWndDemoView::OnNotifySize(UINT wParam, LONG lParam)
{	
	CRect rcMCI;
	CFrameWnd* pParent = GetParentFrame();

	if(m_hMCIWnd)
	{
		::GetWindowRect(m_hMCIWnd, rcMCI);
		pParent->CalcWindowRect(rcMCI, CWnd::adjustBorder);
		CSize size(rcMCI.Width(), rcMCI.Height());
		if(GetExStyle() & WS_EX_CLIENTEDGE)
		{		
			size.cx += 4;
			size.cy += 44;
		}
		pParent->SetWindowPos(NULL, 0, 0, size.cx, size.cy, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE);
	}
	else
	{
		pParent->SetWindowPos(NULL, 0, 0, 320, 160, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE);
	}

	return 1L;
}