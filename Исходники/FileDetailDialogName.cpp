void CFileDetailDialogName::OnNMRclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UINT flag = MF_STRING;
	if (m_listFileNames.GetNextItem(-1, LVIS_SELECTED | LVIS_FOCUSED) == -1)
		flag = MF_GRAYED;

	POINT point;
	::GetCursorPos(&point);
	CTitleMenu popupMenu;
	popupMenu.CreatePopupMenu();
	popupMenu.AppendMenu(flag,MP_MESSAGE, GetResString(IDS_TAKEOVER));
	popupMenu.AppendMenu(flag,MP_COPYSELECTED, GetResString(IDS_COPY));
	popupMenu.AppendMenu(MF_STRING,MP_RESTORE, GetResString(IDS_SV_UPDATE));
	popupMenu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, point.x, point.y, this);
	VERIFY( popupMenu.DestroyMenu() );

	*pResult = 0;
}