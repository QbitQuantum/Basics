void CKadLookupGraph::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, MP_AUTOKADLOOKUPGRAPH, GetResString(IDS_AUTOKADLOOKUPGRAPH));
	menu.CheckMenuItem(MP_AUTOKADLOOKUPGRAPH , thePrefs.GetAutoShowLookups() ? MF_CHECKED : MF_UNCHECKED);
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}