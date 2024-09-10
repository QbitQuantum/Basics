void CFPAnalysisView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
   	if (currentimage.OK())
	{
		CMenu MenuBar;
		MenuBar.LoadMenu(IDR_FPANALTYPE);
		CMenu* pMenu = MenuBar.GetSubMenu(2);
		
		pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	}
	else
	{
		CScrollView::OnContextMenu(pWnd,point);
	}
}