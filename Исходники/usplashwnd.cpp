BOOL USplashWindow::filterMessage(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	if ((uMessage == WM_KEYDOWN	   ||
		 uMessage == WM_SYSKEYDOWN	   ||
		 uMessage == WM_LBUTTONDOWN   ||
		 uMessage == WM_RBUTTONDOWN   ||
		 uMessage == WM_MBUTTONDOWN   ||
		 uMessage == WM_NCLBUTTONDOWN ||
		 uMessage == WM_NCRBUTTONDOWN ||
		 uMessage == WM_NCMBUTTONDOWN))
	{
		this->killFlash();
		killTimer(ID_SPLASH_TIMER);
		return TRUE;
	}

	return UBaseWindow::filterMessage(uMessage, wParam, lParam);
}