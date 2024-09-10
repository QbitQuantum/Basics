void PixelLightCtrl::SetTrapMouse(bool bTrap)
{
	if (m_hFrontendWnd) {
		// Trap mouse?
		if (bTrap) {
			// Get window rect (in screen coordinates)
			RECT sRect;
			GetWindowRect(&sRect);

			// Trap mouse
			ClipCursor(&sRect); 
		} else {
			// Untrap mouse
			ClipCursor(nullptr);
		}

		// Backup the state
		m_bTrapMouse = bTrap;
	}
}