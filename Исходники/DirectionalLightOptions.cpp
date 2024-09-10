	void DirectionalLightOptions::init(HINSTANCE hInstance, HWND hParentWnd,
							    const SubwindowDesc subwindowDesc)
	{
		initWindow(hInstance, hParentWnd, subwindowDesc,
				   WS_POPUP | WS_CAPTION | WS_CHILD,
				   m_trackbarSize.x + 2 * m_trackbarMargin, m_trackbarMargin,
				   6001);

		SetWindowSubclass(m_hWnd, DirectionalLightOptionsMsgRouter, 0, 0);
	}