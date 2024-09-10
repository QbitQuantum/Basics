void CDemoView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
	CDemoDoc* pDoc = GetDocument();
	if (pDoc && pDoc->m_tool==2) return;
#ifdef VATI_EXTENSIONS
	// suppress context menu if right-click function was called just now
	if ( m_suppressContextMenu == true )
		return;
#endif
	static UINT toolbars[]={
		IDR_MAINFRAME,
		IDR_TOOLBAR1,
	};
	BCMenu menu;
	menu.LoadMenu(IDM_CXIMAGE1);
	menu.LoadToolbars(toolbars,2);
	CMenu *pContextMenu=menu.GetSubMenu(0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
}