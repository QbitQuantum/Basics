void CTerminalTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CRect rect_Item;

	HTREEITEM hSelItem_cur = HitTest(point);
	if(hSelItem_cur != NULL)
	{
		GetItemRect(hSelItem_cur, &rect_Item, TRUE);
		if(PtInRect(rect_Item, point))
			Select(hSelItem_cur, TVGN_CARET);
		else return;
	}

	HTREEITEM hSelItem = GetSelectedItem();
	if(hSelItem != NULL)
	{
		GetItemRect(hSelItem, &rect_Item, TRUE);

		if(PtInRect(rect_Item, point))
		{
			POINT m_posScreen;
			RECT rect;
			GetWindowRect(&rect);

			m_posScreen.x = rect.left;
			m_posScreen.y = rect.top;
		
			m_posScreen.x += point.x;
			m_posScreen.y += point.y;
            
			ItemData *data = (ItemData *)GetItemData(hSelItem);
			if (data->m_type == ITEM_TYPE_TERMINAL)
			{				
				CMenu menu;
				menu.LoadMenuA(IDR_MAINFRAME);
				menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,m_posScreen.x,m_posScreen.y,this);				
			}			
		}
	}
	
	CTreeCtrl::OnRButtonDown(nFlags, point);
}