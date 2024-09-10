/*
	PopUpMenu()
*/
void CWallBrowserFileView::PopUpMenu(const CPoint& point)
{
	CRect rect;
	CMenu menu;
	CMenu* pSubMenu = NULL;

	// coordinate dell'area client (CWnd, base 0,0)
	CWnd::GetClientRect(&rect);
	
	// trasforma le coordinate in assolute (schermo)
	// da aggiungere alle coordinate del click del mouse per ottenere le coordinate a cui visualizzare il menu a comparsa
	CWnd::ClientToScreen(&rect);	
	
	// click su un elemento del controllo
	if(GetListCtrl().HitTest(point) >= 0)
	{
		if(menu.LoadMenu(IDM_FILEPOPUP))
			pSubMenu = menu.GetSubMenu(0);
	}

	// visualizza il menu popup
	if(pSubMenu)
	{
		pSubMenu->EnableMenuItem(IDM_FILEPOPUP_PASTE,::IsClipboardFormatAvailable(CF_DIB) ? MF_ENABLED : MF_GRAYED);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x+rect.left,point.y+rect.top,this);
	}
}