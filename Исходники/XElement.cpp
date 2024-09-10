VOID CXElement::On_CXMsg_MouseEnter( CXMsg_MouseEnter& arg )
{
	CString toolTip;
	if (XSUCCEEDED(GetToolTip(toolTip)))
	{
		CXMsg_GetRealWnd msg;
		_SendXMsg(msg);
		if (!msg.wnd)
		{
			return;
		}
		HWND hWnd = 0;
		msg.wnd->GetHWnd(hWnd);
		if (!m_toolTip.IsWindow())
		{
			m_toolTip.Create(hWnd, NULL, NULL, TTS_ALWAYSTIP | TTS_NOPREFIX,WS_EX_TOPMOST);
			if (!m_toolTip.IsWindow())
			{
				WTF;
			}
			m_toolTip.SetWindowLongPtr(GWLP_USERDATA,(LONG_PTR)hWnd);

			CSize size;
			GetSize(size);
			m_toolTip.SetMaxTipWidth(260);
			m_toolTip.AddTool(hWnd,_T(""));
			m_toolTip.SetDelayTime( TTDT_AUTOPOP, static_cast<int>(GetDoubleClickTime() * 10) ) ;
			m_toolTip.SetDelayTime( TTDT_RESHOW, static_cast<int>(GetDoubleClickTime() * 10) ) ;
			m_toolTip.Activate(TRUE);
		}
		MSG mouseMsg = { hWnd, WM_MOUSEMOVE, 0, MAKELONG (arg.pt.x,arg.pt.y)};
		m_toolTip.RelayEvent(&mouseMsg);

		m_toolTip.UpdateTipText((LPCTSTR)toolTip,hWnd);
	}
	arg.msgHandled = TRUE;
}