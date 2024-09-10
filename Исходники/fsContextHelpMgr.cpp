void fsContextHelpMgr::ShowMenu()
{
	if (m_iLastCtrl == -1)
		return;

	CMenu menu;
	menu.LoadMenu (IDM_WT);

	CMenu *popup = menu.GetSubMenu (0);
	popup->ModifyMenu (ID_WHATISTHIS, MF_BYCOMMAND|MF_STRING, ID_WHATISTHIS, LS (L_WHATISTHIS));

	popup->TrackPopupMenu (TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN, m_ptLast.x, m_ptLast.y, m_pLastDlg);
}