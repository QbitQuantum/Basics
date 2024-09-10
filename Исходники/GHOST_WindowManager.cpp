GHOST_TSuccess GHOST_WindowManager::endFullScreen(void)
{
	GHOST_TSuccess success = GHOST_kFailure;
	if (getFullScreen()) {
		if (m_fullScreenWindow != NULL) {
			//GHOST_PRINT("GHOST_WindowManager::endFullScreen(): deleting full-screen window\n");
			setWindowInactive(m_fullScreenWindow);
			m_fullScreenWindow->endFullScreen();
			delete m_fullScreenWindow;
			//GHOST_PRINT("GHOST_WindowManager::endFullScreen(): done\n");
			m_fullScreenWindow = NULL;
			if (m_activeWindowBeforeFullScreen) {
				setActiveWindow(m_activeWindowBeforeFullScreen);
			}
		}
		success = GHOST_kSuccess;
	}
	return success;
}