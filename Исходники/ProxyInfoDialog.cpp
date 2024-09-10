void    CProxyInfoDialog::switchOK()
{
    CButton *q = (CButton *)GetDlgItem( IDOK );
    if ( (m_proxyServerName.GetLength() > 0) && (m_proxyPortNumber > 0) )
        q->EnableWindow( TRUE );
    else
        q->EnableWindow( FALSE );
}