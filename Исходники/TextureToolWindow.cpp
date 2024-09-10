	void TextureToolWindow::init(HINSTANCE hInstance, HWND hParentWnd, const SubwindowDesc subwindowDesc)
	{
		initWindow(hInstance, hParentWnd, subwindowDesc,
				   WS_POPUP | WS_CAPTION | WS_CHILD,
				   m_textureButtonsPerRow * (m_textureButtonSize + m_itemMargin) + m_itemMargin, m_itemMargin,
				   4001);

		SetWindowSubclass(m_hWnd, textureToolWindowMsgRouter, 0, 0);

		m_trackbarCount = 0;
	}