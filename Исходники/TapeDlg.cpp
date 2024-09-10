/* #FN#
   Sets up the state of the dialog controls */
void
/* #AS#
   Nothing */
CTapeDlg::
SetDlgState()
{
	CSliderCtrl *pSlider = (CSliderCtrl *)GetDlgItem( IDC_TAPE_SLIDER );
	CFileStatus  fsStatus;

	ASSERT(NULL != pSlider);

	/* Check if there is the pointed cassette file */
	BOOL bTape = _IsPathAvailable( m_szTapeFile ) &&
				 CFile::GetStatus( m_szTapeFile, fsStatus );

	pSlider->SetRange( 1, cassette_max_block + 1, FALSE );
	pSlider->SetTicFreq( (cassette_max_block / 30) + 1 );
	pSlider->SetPageSize( (cassette_max_block / 30) + 1 );
	pSlider->SetPos( cassette_current_block );
	pSlider->EnableWindow( bTape );

	SetDlgItemText( IDC_TAPE_FILE, m_szTapeFile );
	SetDlgItemText( IDC_TAPE_DESC, m_bCasImage ? cassette_description : (bTape ? m_szLabels[ LABEL_NOCASIMAGE ] : "") );

	SetPosInfo( cassette_current_block );

#ifdef WIN_NETWORK_GAMES
	if( ST_KAILLERA_ACTIVE )
	{
		_RdOnlyEdit( IDC_TAPE_FILE,   TRUE  );
		_EnableCtrl( IDC_TAPE_BROWSE, FALSE );
		_EnableCtrl( IDC_TAPE_EJECT,  FALSE );
		_EnableCtrl( IDC_TAPE_REWIND, FALSE );
		_EnableCtrl( IDC_TAPE_SLIDER, FALSE );
	}
	else
#endif
	{
		_EnableCtrl( IDC_TAPE_EJECT,  bTape );
		_EnableCtrl( IDC_TAPE_REWIND, bTape );
	}
} /* #OF# CTapeDlg::SetDlgState */