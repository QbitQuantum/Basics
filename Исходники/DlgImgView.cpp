void CDlgImgView::Size()
{
	// Punt if no window
	if ( !::IsWindow( GetSafeHwnd() ) ) return;

	RECT rect, ctrl;
	GetClientRect( &rect );

	CopyRect( &ctrl, &rect );
	ctrl.bottom = ctrl.top + 32;
	CWnd *pCtrl = GetDlgItem( IDC_TOOLBAR );
	if ( pCtrl != NULL ) 
	{	pCtrl->MoveWindow( &ctrl ); pCtrl->RedrawWindow(); }

	ctrl.top = ctrl.bottom + 1;
	ctrl.bottom = rect.bottom;
	pCtrl = GetDlgItem( IDC_IMG );
	if ( pCtrl != NULL ) 
	{	
		CopyRect( &m_imgrect, &ctrl );

		CWinDc *pdc = m_img.GetShowDc();
		if ( pdc != NULL ) CopyRect( &m_imgrect, *pdc );
		else
		{	CWinImg *pimg = m_img.GetImg();
			if ( pimg != NULL ) CopyRect( &m_imgrect, *pimg );
		} // end if

		CGrDC::Center( &m_imgrect, &ctrl );
		if ( m_imgrect.top < ctrl.top ) OffsetRect( &m_imgrect, 0, ctrl.top - m_imgrect.top );

		pCtrl->MoveWindow( &m_imgrect );

		pCtrl->RedrawWindow(); 

	} // end if

}