void CCommentListCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	UINT flag = MF_STRING;
	if (GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED) == -1)
		flag = MF_GRAYED;

	CTitleMenu popupMenu;
	popupMenu.CreatePopupMenu();
	popupMenu.AppendMenu(MF_STRING | flag, MP_MESSAGE, GetResString(IDS_CMT_COPYCLIPBOARD));

	GetPopupMenuPos(*this, point);
	popupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	VERIFY( popupMenu.DestroyMenu() );
}