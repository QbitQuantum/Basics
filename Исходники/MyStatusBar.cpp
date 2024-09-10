BOOL CMyStatusBar::OnEraseBkgnd(CDC& dc)
{
	// The background can be set here if XP themes are enabled 
	if (IsXPThemed())
	{
		// Fill the background with a color gradient
		dc.GradientFill(RGB(125, 230, 255), RGB(250, 150, 150), GetClientRect(), TRUE); 
		return TRUE;
	}

	return FALSE;
}