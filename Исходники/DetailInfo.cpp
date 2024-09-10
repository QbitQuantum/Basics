void CDetailInfo::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu; // = new CMenu();

	menu.CreatePopupMenu();
	
	menu.AppendMenu(MF_STRING, MP_COPYSELECTED, GetResString(IDS_COPY));
	menu.AppendMenu(MF_STRING, MP_SELECTALL, GetResString(IDS_SELECTALL));

	m_pMenuXP = new CMenuXP();
	m_pMenuXP->AddMenu(&menu, TRUE);
	menu.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, point.x, point.y, this);
	delete m_pMenuXP;
	m_pMenuXP = NULL;
}