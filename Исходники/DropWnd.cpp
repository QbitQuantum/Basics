void CDropWnd::Show()
{
	Filter();
	SetScrollPos(SB_VERT, 0, FALSE);
	if(m_FilterItemCollection.size() <= 10)
		EnableScrollBar(SB_VERT, ESB_DISABLE_BOTH);
	else
	{
		EnableScrollBar(SB_VERT, ESB_ENABLE_BOTH);
		SetScrollRange(SB_VERT, 0, m_FilterItemCollection.size() - 10);
	}

	CDropWnd::m_Hook = ::SetWindowsHookEx(WH_MOUSE, (HOOKPROC)HookMouseProc, NULL, GetCurrentThreadId());
	CDropWnd::m_pDropWnd = this;

	TRACE("CDropWnd::Show\n");
	CRect rt;
	m_pComboBoxWnd->GetWindowRect(&rt);
	SetWindowPos(&wndTopMost, rt.left, rt.top + rt.Height(), 0, 0, SWP_NOSIZE|SWP_SHOWWINDOW|SWP_NOACTIVATE);
}