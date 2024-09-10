BOOL CAboutDlg :: OnInitDialog ( void )
{
    ASSERT ( this ) ;

    // Let the normal processing happen.
    CDialog::OnInitDialog ( ) ;

    // Do the big icon.
    m_cBigIcon.SubclassDlgItem ( IDC_BIGICON , this ) ;
    m_cBigIcon.SizeToContent ( ) ;

    // Create and set the name font.
    m_pcFont = new CFont ;
    BOOL bRet = m_pcFont->CreatePointFont ( 300 , _T ( "Arial" ) ) ;
    ASSERT ( bRet ) ;
    if ( TRUE == bRet )
    {
        CWnd * pWnd = GetDlgItem ( IDC_APPNAME ) ;
        ASSERT ( NULL != pWnd ) ;
        if ( NULL != pWnd )
        {
            pWnd->SetFont ( m_pcFont ) ;
        }
    }
    m_cRedText.SubclassDlgItem ( IDC_APPNAME , this ) ;


    // Stick the hint text into the edit control.
    HRSRC hRes = ::FindResource ( NULL                             ,
                                  MAKEINTRESOURCE ( IDR_HINTDATA ) ,
                                  _T ( "HINTDATA" )                 ) ;
    ASSERT ( NULL != hRes ) ;
    if ( NULL != hRes )
    {
        LPCTSTR szData = (LPCTSTR)::LoadResource ( NULL , hRes ) ;
        ASSERT ( NULL != szData ) ;

        CWnd * pEdit = GetDlgItem ( IDC_HINTS ) ;
        ASSERT ( NULL != pEdit ) ;

        pEdit->SetWindowText ( szData ) ;

    }

    // Get the hyperlink thing hooked up.
    //m_cWebLink.m_link = _T ( "www.wintellect.com" ) ;
    m_cWebLink.SubclassDlgItem ( IDC_HYPERLINK , this ) ;

    // Put the focus on the OK button.
    CWnd * pOK = GetDlgItem ( IDOK ) ;
    ASSERT ( NULL != pOK ) ;

    pOK->SetFocus ( ) ;

    return ( FALSE ) ;
}