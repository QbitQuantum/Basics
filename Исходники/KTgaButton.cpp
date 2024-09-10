void KTgaButton::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_pOutDoorMgr && m_nButtonType == GROUNDTEXTURE)
		return ;
	CButton::OnRButtonUp(nFlags, point);

	POINT point1;
	GetCursorPos(&point1);
	CMenu* pMenu = m_MenuTga.GetSubMenu(0);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point1.x, point1.y, this);
	CButton::OnRButtonUp(nFlags, point);


}