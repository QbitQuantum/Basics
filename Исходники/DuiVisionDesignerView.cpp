/////////////////////////////////////////////////////////////////////////////
// CDuiVisionDesignerView message handlers
void CDuiVisionDesignerView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	get_dll_resource();
	CMenu* pMenu = new CMenu();
	pMenu->LoadMenu(IDR_OWM);
	reset_dll_resource();
	CMenu* pmenu = (CMenu*)pMenu->GetSubMenu(0);
	pmenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
			point.x, point.y, this);
	delete pMenu;
}