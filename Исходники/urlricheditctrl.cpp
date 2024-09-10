void CUrlRichEditCtrl::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   if (nChar == VK_F10 && GetKeyState(VK_SHIFT))
	{
		m_ptContextMenu = GetCaretPos();

		// does this location lie on a url?
		m_nContextUrl = FindUrl(m_ptContextMenu);
		
		// convert point to screen coords
		ClientToScreen(&m_ptContextMenu);
		
		// eat message else we'll get a WM_KEYUP with VK_APPS
	}
	
	CRichEditBaseCtrl::OnSysKeyDown(nChar, nRepCnt, nFlags);
}