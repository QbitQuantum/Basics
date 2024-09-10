	void NewTerrainWindow::init(HINSTANCE hInstance, HWND hParentWnd, const SubwindowDesc subwindowDesc)
	{
		initWindow(hInstance, hParentWnd, subwindowDesc,
				   WS_POPUP | WS_CAPTION | WS_CHILD,
				   2 * (m_dropdownListWidth + m_itemMargin) + m_itemMargin, m_itemMargin,
				   7001);

		SetWindowSubclass(m_hWnd, newTerrainWindowMsgRouter, 0, 0);
	}