void TwitterAuthSelectDialog::ShowCurrentStatus( bool rescan /* = FALSE */ )
{
    CButton *bp = (CButton *)GetDlgItem( IDC_BUTTON_GET_TOKEN );
    bp->EnableWindow( m_useOAuth );

    bp = (CButton *)GetDlgItem( IDC_RADIO_OAUTH );
    bp->SetCheck( m_useOAuth ? 1 : 0 );

    bp = (CButton *)GetDlgItem( IDC_RADIO_BASIC );
    bp->SetCheck( m_useBASIC ? 1 : 0 );

    CString status;
    CStatic *sp = (CStatic *)GetDlgItem( IDC_TOKEN_STATUS );
    if ( (m_oauthToken.GetLength()       > 0) &&
         (m_oauthTokenSecret.GetLength() > 0)    )
	    status.LoadString( IDS_ACCESSTOKEN_ACQUIRED );
    else
	    status.LoadString( IDS_ACCESSTOKEN_UNTAKEN );
    sp->SetWindowText( status );

    CEdit   *p = (CEdit *)GetDlgItem(IDC_EDIT_USERNAME);
    if ( rescan )
        p->GetWindowText( m_username );
    p->SetWindowText( m_username );
    p->EnableWindow( m_useBASIC );

    p = (CEdit *)GetDlgItem(IDC_EDIT_PASSWORD);
    if ( rescan )
        p->GetWindowText( m_password );
    p->SetWindowText( m_password );
    p->EnableWindow( m_useBASIC );
}