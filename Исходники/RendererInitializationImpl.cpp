/// Callback executed when the main window is actually destroyed.
///
/// @param[in] pWindow  Pointer to the destroyed Window instance.
void RendererInitializationImpl::OnMainWindowDestroyed( Window* pWindow )
{
	HELIUM_ASSERT( m_pMainWindow == pWindow );
	HELIUM_UNREF( pWindow );

#if HELIUM_OPENGL
	// Immediately shut down, since we use GLFW to manage windows, and GLFW
	// windows are inseparable from their render contexts.  Therefore, by the
	// time we've received this callback, our renderer had better be shutting down.
	Renderer* pRenderer = Renderer::GetStaticInstance();
	pRenderer->Shutdown();
#endif

	m_pMainWindow = NULL;
	WindowManager* pWindowManager = WindowManager::GetStaticInstance();
	HELIUM_ASSERT( pWindowManager );
	pWindowManager->RequestQuit();
}