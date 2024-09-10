//-----------------------------------------------------------------------------
// main application
//-----------------------------------------------------------------------------
void CVsVGuiWindow::Detach()
{
	if ( m_hTimerCallbackId != 0 )
	{
		MTimerMessage::removeCallback( m_hTimerCallbackId );
		m_hTimerCallbackId = 0;
	}

	if ( m_hMainPanel.Get() )
	{
		m_hMainPanel->MarkForDeletion();
		m_hMainPanel = NULL;
	}

	if ( m_hVGuiContext != vgui::DEFAULT_VGUI_CONTEXT )
	{
		vgui::ivgui()->DestroyContext( m_hVGuiContext );
		m_hVGuiContext = vgui::DEFAULT_VGUI_CONTEXT;
	}

	// detach
	if ( m_hWnd )
	{
		// kill the timer if any
		g_pMaterialSystem->RemoveView( m_hWnd );
		RemoveWindowSubclass( m_hWnd, SubclassCallback, s_subclassId );
		m_hWnd = NULL;
	}

	if ( m_hKeyFocusWnd )
	{
		RemoveWindowSubclass( m_hKeyFocusWnd, KeyFocusSubclassCallback, s_subclassId );
		m_hKeyFocusWnd = NULL;
	}
}