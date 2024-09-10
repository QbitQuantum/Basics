void CPgChromaKey::DoEnable()
{
	UpdateData( TRUE );

	CWnd *pCtrl = GetDlgItem( IDC_NOSMOOTHING );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );

	pCtrl = GetDlgItem( IDC_NEGATIVE );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );
	pCtrl = GetDlgItem( IDC_SLIDENEGATIVE );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );

	pCtrl = GetDlgItem( IDC_POSITIVE );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );
	pCtrl = GetDlgItem( IDC_SLIDEPOSITIVE );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );

	pCtrl = GetDlgItem( IDC_COLORBOX );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );
	pCtrl = GetDlgItem( IDC_CHOOSE_COLOR );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );

	pCtrl = GetDlgItem( IDC_BOX );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );
	pCtrl = GetDlgItem( IDC_TXT_POSITIVE );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );
	pCtrl = GetDlgItem( IDC_TXT_NEGATIVE );
	if ( pCtrl != NULL ) pCtrl->EnableWindow( m_bEnable );
}