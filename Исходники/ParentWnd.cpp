CParentWnd::~CParentWnd()
{
	// Since we didn't create a window, we can't call DestroyWindow to let MFC know we're done.
	// We call AfxPostQuitMessage instead
	TRACE_DESTRUCTOR(CLASS);
	UninitializeGDI();
	UnloadAddIns();
	if (m_hwinEventHook) UnhookWinEvent(m_hwinEventHook);
	UninitializeNamedPropCache();
	WriteToRegistry();
	CloseDebugFile();
	// Since we're killing what m_pMainWnd points to here, we need to clear it
	// Else MFC will try to route messages to it
	theApp.m_pMainWnd = NULL;
	AfxPostQuitMessage(0);
} // CParentWnd::~CParentWnd