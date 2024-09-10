void CSpiderTaskTree::ShowContextMenu()
{
	HTREEITEM hItem = GetSelectedItem ();
	if (hItem == NULL)
		return;

	int iItem = FindTree (hItem);
	if (iItem == -1)
		return;

	CMenu menu;
	menu.LoadMenu (IDM_SPIDER_TREE);
	CMenu *pPopup = menu.GetSubMenu (0);

	CString str = LS (L_DONTDOWNLOADANDDEL); str += "\tDel";
	menu.ModifyMenu (ID_DONTDOWNLOADANDDEL, MF_BYCOMMAND|MF_STRING, ID_DONTDOWNLOADANDDEL, str);

	fsDLWebPage *wp = m_vConfs [iItem].wptree->GetData ();
	if (wp->dld == NULL || wp->dld->pMgr->IsDone ())
		pPopup->EnableMenuItem (ID_DONTDOWNLOADANDDEL, MF_BYCOMMAND | MF_GRAYED);

	ClientToScreen (&m_rbPt);
	pPopup->TrackPopupMenu (TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN,	m_rbPt.x, m_rbPt.y, this);
	menu.DestroyMenu ();
}