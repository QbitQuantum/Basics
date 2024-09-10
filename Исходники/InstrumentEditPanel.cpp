void CSequenceInstrumentEditPanel::OnRClickInstSettings(NMHDR* pNMHDR, LRESULT* pResult)
{
	POINT oPoint;
	GetCursorPos(&oPoint);

	if (m_pSequence == NULL)
		return;

	// Display clone menu
	CMenu contextMenu;
	contextMenu.LoadMenu(IDR_SEQUENCE_POPUP);
	CMenu *pMenu = contextMenu.GetSubMenu(0);
	pMenu->EnableMenuItem(ID_CLONE_SEQUENCE, (m_pSequence->GetItemCount() != 0) ? FALSE : TRUE);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, oPoint.x, oPoint.y, this);
}