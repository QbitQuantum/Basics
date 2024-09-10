void PopupManager::Show(const tstring &aMsg, const tstring &aTitle, int Icon, bool preview /*= false*/)
{
	dcassert(ClientManager::isStartup() == false);
	dcassert(ClientManager::isShutdown() == false);
	if (ClientManager::isShutdown())
		return;
	if (ClientManager::isStartup())
		return;
		
	if (!m_is_activated)
		return;
		
		
	if (!Util::getAway() && BOOLSETTING(POPUP_AWAY) && !preview)
		return;
		
	if (!MainFrame::isAppMinimized() && BOOLSETTING(POPUP_MINIMIZED) && !preview)
		return;
		
	tstring msg = aMsg;
	if (int(aMsg.length()) > SETTING(MAX_MSG_LENGTH))
	{
		msg = aMsg.substr(0, (SETTING(MAX_MSG_LENGTH) - 3));
		msg += _T("...");
	}
#ifdef _DEBUG
	msg += Text::toT(" m_popups.size() = " + Util::toString(m_popups.size()));
#endif
	
	if (SETTING(POPUP_TYPE) == BALLOON && MainFrame::getMainFrame())
	{
		NOTIFYICONDATA m_nid = {0};
		m_nid.cbSize = sizeof(NOTIFYICONDATA);
		m_nid.hWnd = MainFrame::getMainFrame()->m_hWnd;
		m_nid.uID = 0;
		m_nid.uFlags = NIF_INFO;
		m_nid.uTimeout = (SETTING(POPUP_TIME) * 1000);
		m_nid.dwInfoFlags = Icon;
		_tcsncpy(m_nid.szInfo, msg.c_str(), 255);
		_tcsncpy(m_nid.szInfoTitle, aTitle.c_str(), 63);
		Shell_NotifyIcon(NIM_MODIFY, &m_nid);
		return;
	}
	
	if (m_popups.size() > 10)
	{
		//LogManager::message("PopupManager - m_popups.size() > 10! Ignore");
		return;
	}
	
	if (SETTING(POPUP_TYPE) == CUSTOM && PopupImage != SETTING(POPUPFILE))
	{
		PopupImage = SETTING(POPUPFILE);
		m_popuptype = SETTING(POPUP_TYPE);
		m_hBitmap = (HBITMAP)::LoadImage(NULL, Text::toT(PopupImage).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}
	
	height = SETTING(POPUP_H);
	width = SETTING(POPUP_W);
	
	CRect rcDesktop;
	
	//get desktop rect so we know where to place the popup
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
	
	int screenHeight = rcDesktop.bottom;
	int screenWidth = rcDesktop.right;
	
	//if we have popups all the way up to the top of the screen do not create a new one
	if ((offset + height) > screenHeight)
		return;
		
	//get the handle of the window that has focus
	dcassert(WinUtil::g_mainWnd);
	HWND gotFocus = ::SetFocus(WinUtil::g_mainWnd);
	
	//compute the window position
	CRect rc(screenWidth - width , screenHeight - height - offset, screenWidth, screenHeight - offset);
	
	//Create a new popup
	PopupWnd *p = new PopupWnd(msg, aTitle, rc, m_id++, m_hBitmap);
	p->height = height; // save the height, for removal
	
	if (SETTING(POPUP_TYPE) != /*CUSTOM*/ BALLOON)
	{
		typedef bool (CALLBACK * LPFUNC)(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
		LPFUNC _d_SetLayeredWindowAttributes = (LPFUNC)GetProcAddress(LoadLibrary(_T("user32")), "SetLayeredWindowAttributes");
		if (_d_SetLayeredWindowAttributes)
		{
			p->SetWindowLongPtr(GWL_EXSTYLE, p->GetWindowLongPtr(GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
			_d_SetLayeredWindowAttributes(p->m_hWnd, 0, SETTING(POPUP_TRANSP), LWA_ALPHA);
		}
	}
	
	//move the window to the top of the z-order and display it
	p->SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	p->ShowWindow(SW_SHOWNA);
	
	//restore focus to window
	::SetFocus(gotFocus);
	
	//increase offset so we know where to place the next popup
	offset = offset + height;
	
	m_popups.push_back(p);
}