void CBmpTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	AfxMessageBox("dd");
	//m_dwState=HTHDOWN;
	CRect rcItem;
	for(int i=0;i<m_aryItem.GetSize();i++)
	{
		CWnd *tabItemView;
		tabItemView=(CWnd*)((TABITEM*)m_aryItem.GetAt(i))->pVoid;
		if(tabItemView)
			tabItemView->ShowWindow(SW_HIDE);

		GetTabItemRect(i,&rcItem);
		if(rcItem.PtInRect(point))
		{
			m_iCurrentSelect=i;
			if((m_aryItem.GetAt(i))!=NULL)
			{
				if(tabItemView)
					tabItemView->ShowWindow(SW_NORMAL);
			}
		}
		
	}
	Invalidate();
	CStatic::OnLButtonDown(nFlags, point);
}