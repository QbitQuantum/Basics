LONG TextViewBase::OnSetFocus(HWND hwndOld)
{
	//CreateCaret(m_hWnd, (HBITMAP)NULL, m_nCaretWidth, m_nLineHeight);
	m_bFocused = true;
	CreateMyCaret();
	RepositionCaret();

	ShowCaret(m_hWnd);
	RefreshWindow();
	return 0;
}