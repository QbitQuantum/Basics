void CDragVirtualListCtrl::UpdateCursor(CPoint point)
{
	if (ChildWindowFromPoint(point) == this)
		SetCursor(AfxGetApp()->LoadCursor(IDC_DRAG_SINGLE));
	else
 		SetCursor(LoadCursor(NULL, IDC_NO));
}