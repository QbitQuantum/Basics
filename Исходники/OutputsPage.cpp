void COutputsPage::OnPMixSelect( UINT nID )
/////////////////////////////////////////////////////////////////////////////
{
	CMenu	Menu;
	CMenu	PopupMenu;
	CPoint	Point;
	int		nDst, nSrc;
	ULONG	ulValue;

	m_nPlaySelectID = nID;	// remember which control launced the popup menu

	nDst = (m_nPlaySelectID - IDC_OUT1_PMIXA_SELECT) /
			(IDC_OUT2_PMIXA_SELECT - IDC_OUT1_PMIXA_SELECT);

	nSrc = ((m_nPlaySelectID - IDC_OUT1_PMIXA_SELECT) - (nDst * (IDC_OUT2_PMIXA_SELECT - IDC_OUT1_PMIXA_SELECT))) / 
			((IDC_OUT1_PMIXD_SELECT - IDC_OUT1_PMIXA_SELECT) / 2);

	m_pHalMixer->GetControl( LINE_OUT_1 + nDst, LINE_PLAY_MIXA + nSrc, CONTROL_SOURCE, 0, &ulValue );

	Menu.LoadMenu( IDR_OUTPUT_SOURCE );
	PopupMenu.Attach( Menu.GetSubMenu( 0 )->m_hMenu );
	
	GetCursorPos( &Point );
	PopupMenu.CheckMenuItem( IDM_SOURCE_RECORD1LEFT + ulValue, MF_BYCOMMAND | MF_CHECKED );
	PopupMenu.TrackPopupMenu( TPM_LEFTALIGN, Point.x, Point.y, this, NULL );
}