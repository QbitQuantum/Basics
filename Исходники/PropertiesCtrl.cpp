void CPropertiesCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu Popup;
	Popup.LoadMenu(IDR_POPUP_MENUS);
	CMenu* pPopup = Popup.GetSubMenu(5);
	ASSERT(pPopup);
	CRect rc;

	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,	point.x, point.y, GetParentFrame(), NULL/*&rc*/);
	
}