void CD3DApp::DestroyD3DApp()
{
	g_uiWndWidth = 0;
	g_uiWndHeight = 0;
	m_wWndPosX = 0;
	m_wWndPosY = 0;
	m_bFullscreen = 0;
	m_liCountNum = 0;
	m_liLastCountNum = 0;
	m_bPaused = 1;

	m_hInst = 0; 
	g_hWnd = 0;
	g_uiWndWidth = 0;
	g_uiWndHeight = 0;

	ReleaseX(g_pSwapChain);
	ReleaseX(g_pD3DDevice);
	ReleaseX(m_pDinput);
	m_pKeyboard->Unacquire();
	ReleaseX(m_pKeyboard);
	m_pMouse->Unacquire();
	ReleaseX(m_pMouse);

	UnregisterClassW(m_szWndClassName, m_hInst);
	delete[] m_szWndClassName;
	m_szWndClassName = NULL;
	delete[] m_szWndTitleText;
	m_szWndTitleText = NULL;
}