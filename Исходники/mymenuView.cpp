void CMymenuView::OnRButtonDown(UINT /*nFlags*/, CPoint point) //SK: removed warning C4100: 'nFlags' : unreferenced formal parameter
{
	popmenu.LoadMenu(IDR_RIGHT_CLICK);
	popmenu.LoadToolbar(IDR_TOOLBAR);
	popmenu.LoadToolbar(IDR_MAINFRAME);
	ClientToScreen(&point);
	BCMenu *psub = (BCMenu *)popmenu.GetSubMenu(0);
	BCMenu *pSelect = (BCMenu *)psub->GetSubMenu(1);
	if(pSelect){
		pSelect->AppendMenu(MF_STRING,ID_WINDOW_TILE_HORZ,_T("&Tile"));
		pSelect->ModifyODMenu(NULL,ID_WINDOW_TILE_HORZ,IDB_WINDOW_TILE);
	}
	psub->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());
	popmenu.DestroyMenu();
}