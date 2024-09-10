void CWnd_FDMGetCustVer_Btn::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu (IDM_GCV_BUTTON);
	CMenu *pPopup = menu.GetSubMenu (0);

	CPoint pt; GetCursorPos (&pt);

	m_odmenu.Attach (&menu, FALSE);

	pPopup->ModifyMenu (ID_HIDE, MF_BYCOMMAND|MF_STRING, ID_HIDE, LS (L_HIDE));

	
	pPopup->TrackPopupMenu (TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,	pt.x, pt.y, this);

	m_odmenu.Detach ();
	menu.DestroyMenu ();
	
	CWnd::OnRButtonUp(nFlags, point);
}