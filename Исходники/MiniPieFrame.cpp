BOOL CMiniPieFrame::SetCommandButton(INT iID, bool bRight)
{
	TBBUTTONINFO tbbi = { sizeof(TBBUTTONINFO), TBIF_TEXT | TBIF_COMMAND | TBIF_BYINDEX };
	tbbi.idCommand =  iID;
	tbbi.pszText = (LPTSTR)AtlLoadString(iID);
	return CMenuBarCtrl(m_hWndCECommandBar).SetButtonInfo(bRight, &tbbi);
}