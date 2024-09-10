void CPianoCtrl::SetPressed(int KeyIdx, bool Enable, bool External)
{
	CKey&	key = m_Key[KeyIdx];
	if (Enable == key.m_IsPressed)	// if key already in requested state
		return;	// nothing to do
	DWORD	dwStyle = GetStyle();
	if (dwStyle & PS_HIGHLIGHT_PRESS)	// if indicating pressed keys
		InvalidateRgn(&key.m_Rgn);	// mark key for repainting
	key.m_IsPressed = Enable;
	key.m_IsExternal = External;
	if (!External) {	// if key pressed by us
		CWnd	*pParentWnd = GetParent();	// notify parent window
		ASSERT(pParentWnd != NULL);
		pParentWnd->SendMessage(UWM_PIANOKEYCHANGE, KeyIdx, LPARAM(m_hWnd));
	}
}