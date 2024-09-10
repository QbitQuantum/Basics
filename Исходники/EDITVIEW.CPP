bool CScriptEditView::QueryClose()
{
	if( !GetModify() )
		return true;

	TCHAR szFmt[32];
	AtlLoadString( IDS_SAVE_MODIFIED, szFmt, DIMOF(szFmt) );
	TCHAR szBuff[MAX_PATH + 40];
	wsprintf( szBuff, szFmt, m_szFileName );
	int nRet = AtlMessageBox(
		WtlGetMainWnd(),
		szBuff,
		IDR_MAINFRAME,
		MB_YESNOCANCEL | MB_ICONEXCLAMATION
		);

	if(nRet == IDCANCEL)
		return false;

	if(nRet == IDYES)
		return OnFileSave();

	return true;
}