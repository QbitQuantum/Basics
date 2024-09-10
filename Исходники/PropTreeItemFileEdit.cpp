void CPropTreeItemFileEdit::OnContextMenu(CWnd *pWnd, CPoint point)
{

	CMenu FloatingMenu;
	VERIFY(FloatingMenu.LoadMenu(IDR_ME_EDIT_MENU));
	CMenu *pPopupMenu = FloatingMenu.GetSubMenu(0);

	if (CanUndo()) {
		pPopupMenu->EnableMenuItem(ID_EDIT_UNDO, MF_BYCOMMAND | MF_ENABLED);
	} else {
		pPopupMenu->EnableMenuItem(ID_EDIT_UNDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	DWORD dwSel = GetSel();

	if (HIWORD(dwSel) != LOWORD(dwSel)) {
		pPopupMenu->EnableMenuItem(ID_EDIT_CUT, MF_BYCOMMAND | MF_ENABLED);
		pPopupMenu->EnableMenuItem(ID_EDIT_COPY, MF_BYCOMMAND | MF_ENABLED);
		pPopupMenu->EnableMenuItem(ID_EDIT_DELETE, MF_BYCOMMAND | MF_ENABLED);
	} else {
		pPopupMenu->EnableMenuItem(ID_EDIT_CUT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pPopupMenu->EnableMenuItem(ID_EDIT_COPY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pPopupMenu->EnableMenuItem(ID_EDIT_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}