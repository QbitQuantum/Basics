void COptionsGeneral::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if( !pScrollBar || !m_bManualThumbChange)
		return;
	
	CSliderCtrl * pSlider = reinterpret_cast<CSliderCtrl*>( pScrollBar );
	
	if( pSlider && pSlider->GetDlgCtrlID() == IDC_WIDTH_SLIDER )
	{
		int pos = pSlider->GetPos();

		if( m_nThumbnailWidth != pos )
		{
			if( m_bSyncChangeThumbSize )
			{
				int nNewHeight = int(pos/m_fAspect);
				int nMaxHeight, nMinHeight;
				
				m_ThumbHeightSlider.GetRange( nMinHeight, nMaxHeight );
				if( nNewHeight < nMinHeight || nNewHeight > nMaxHeight )
				{
					MessageBeep( MB_ICONEXCLAMATION );
					pSlider->SetPos( m_nThumbnailWidth);
				}
				else
				{
					CSCADString str;

					m_nThumbnailWidth = pos;
					m_nThumbnailHeight = nNewHeight;
					m_bManualThumbChange = false;
					m_ThumbHeightSlider.SetPos( m_nThumbnailHeight);
					m_bManualThumbChange = true;
					str.Format( _T("%d"), m_nThumbnailWidth );
					GetDlgItem( IDC_WIDTH_EDIT )->SetWindowText( str );
					str.Format( _T("%d"), m_nThumbnailHeight );
					GetDlgItem( IDC_HEIGHT_EDIT )->SetWindowText( str );
				}
			}
			else
			{
				CSCADString str;

				str.Format( _T("%d"), pos );
				GetDlgItem( IDC_WIDTH_EDIT )->SetWindowText( str );
				m_nThumbnailWidth = pos;
			}
			UpdateThumbnail();

		}
	}
}