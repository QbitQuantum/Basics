void CPgPubExtra::OnSettings() 
{
	CReg *pReg = (CReg*)CDlgTabFrame::GetData( GetSafeHwnd() );
	if ( pReg == NULL ) return;
	CRKey *pRk = pReg->FindKey( "PUBINFO" );
	if ( pRk == NULL ) return;

	int sel = m_comboCodec.GetCurSel();
	if ( sel == CB_ERR ) return;

	// Get data pointer
	LPCODECINFO pci = (LPCODECINFO)m_comboCodec.GetItemData( sel );
	if ( pci == NULL || !m_codecs.VerifyPointer( pci ) ) return;

	// Attempt to open settings dialog
	HIC hIc = ICOpen( ICTYPE_VIDEO, pci->fourCC, ICMODE_QUERY );
	if ( hIc != NULL )
	{
		DWORD size = pRk->GetValueSize( "CodecData" );
		LPBYTE buf = (LPBYTE)pRk->GetValuePtr( "CodecData" );

		// Restore settings
		if ( size > 0 && buf != NULL )
			ICSetState( hIc, buf, size );

		// Configure the compressor
		if ( ICConfigure( hIc, GetSafeHwnd() ) != ICERR_OK )
			return;

		size = ICGetStateSize( hIc );
		if ( size > 0 )
		{
			TMem< BYTE > mem;
			if ( mem.allocate( size ) )
				if ( ICGetState( hIc, mem.ptr(), size ) == ICERR_OK )
					pRk->Set( "CodecData", mem.ptr(), size );

		} // end if

		ICClose( hIc ); 

	} // end if
	
}