void CRichEditCtrlX::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	if (point.x != -1 || point.y != -1) {
		CRect rcClient;
		GetClientRect(&rcClient);
		ClientToScreen(&rcClient);
		if (!rcClient.PtInRect(point)) {
			Default();
			return;
		}
	}

	long iSelStart, iSelEnd;
	GetSel(iSelStart, iSelEnd);
	int iTextLen = GetWindowTextLength();

	// Context menu of standard edit control
	// 
	// Undo
	// ----
	// Cut
	// Copy
	// Paste
	// Delete
	// ------
	// Select All

	bool bReadOnly = (GetStyle() & ES_READONLY)!=0;

	// ==> XP Style Menu [Xanatos] - Stulle
	/*
	CMenu menu;
	menu.CreatePopupMenu();
	if (!bReadOnly){
		menu.AppendMenu(MF_STRING, MP_UNDO, GetResString(IDS_UNDO));
		menu.AppendMenu(MF_SEPARATOR);
	}
	if (!bReadOnly)
		menu.AppendMenu(MF_STRING, MP_CUT, GetResString(IDS_CUT));
	menu.AppendMenu(MF_STRING, MP_COPYSELECTED, GetResString(IDS_COPY));
	if (!bReadOnly){
		menu.AppendMenu(MF_STRING, MP_PASTE, GetResString(IDS_PASTE));
		menu.AppendMenu(MF_STRING, MP_REMOVESELECTED, GetResString(IDS_DELETESELECTED));
	}
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, MP_SELECTALL, GetResString(IDS_SELECTALL));
	*/
	CTitleMenu menu;
	menu.CreatePopupMenu();
	menu.AddMenuTitle(GetResString(IDS_LOGENTRY));
	if (!bReadOnly){
		menu.AppendMenu(MF_STRING, MP_UNDO, GetResString(IDS_UNDO), _T("UNDO"));
		menu.AppendMenu(MF_SEPARATOR);
	}
	if (!bReadOnly)
		menu.AppendMenu(MF_STRING, MP_CUT, GetResString(IDS_CUT), _T("CUT"));
	menu.AppendMenu(MF_STRING, MP_COPYSELECTED, GetResString(IDS_COPY), _T("COPY"));
	if (!bReadOnly){
		menu.AppendMenu(MF_STRING, MP_PASTE, GetResString(IDS_PASTE), _T("PASTE"));
		menu.AppendMenu(MF_STRING, MP_REMOVESELECTED, GetResString(IDS_DELETESELECTED), _T("DELETE"));
	}
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, MP_SELECTALL, GetResString(IDS_SELECTALL), _T("SEARCHFILETYPE_DOCUMENT"));
	// <== XP Style Menu [Xanatos] - Stulle

	menu.EnableMenuItem(MP_UNDO, CanUndo() ? MF_ENABLED : MF_GRAYED);
	menu.EnableMenuItem(MP_CUT, iSelEnd > iSelStart ? MF_ENABLED : MF_GRAYED);
	menu.EnableMenuItem(MP_COPYSELECTED, iSelEnd > iSelStart ? MF_ENABLED : MF_GRAYED);
	menu.EnableMenuItem(MP_PASTE, CanPaste() ? MF_ENABLED : MF_GRAYED);
	menu.EnableMenuItem(MP_REMOVESELECTED, iSelEnd > iSelStart ? MF_ENABLED : MF_GRAYED);
	menu.EnableMenuItem(MP_SELECTALL, iTextLen > 0 ? MF_ENABLED : MF_GRAYED);

	if (point.x == -1 && point.y == -1)
	{
		point.x = 16;
		point.y = 32;
		ClientToScreen(&point);
	}
	// Cheap workaround for the "Text cursor is showing while context menu is open" glitch. It could be solved properly 
	// with the RE's COM interface, but because the according messages are not routed with a unique control ID, it's not 
	// really useable (e.g. if there are more RE controls in one window). Would to envelope each RE window to get a unique ID..
	m_bForceArrowCursor = true;
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	m_bForceArrowCursor = false;
	VERIFY( menu.DestroyMenu() ); // XP Style Menu [Xanatos] - Stulle
}