void CTilePanel::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// WM_MOUSEWHEEL 메세지를 받기위해서 다른 컨트롤에 포커스를 맞춘다.
	CWnd *pwnd = GetDlgItem( IDC_STATIC_CHUNKPOS );
	pwnd->SetFocus();
	m_bDrag = TRUE;
	GetCursorPos( &m_ptClickPos );
	SetCapture();
	CPanelBase::OnLButtonDown(nFlags, point);
}