// Now run off WM_CONTEXTMENU: if user wants standard handling, then let him have it
void COXSizeControlBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (m_Style & SZBARF_STDMOUSECLICKS)
	{
		CMenu menu;
		if (menu.CreatePopupMenu())
		{
			OnAddContextMenuItems(0,(LPARAM)menu.m_hMenu);
			menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}
	} 
	else
	{
		CControlBar::OnContextMenu(pWnd, point);
	}
}