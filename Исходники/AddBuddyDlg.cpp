void CAddBuddyDlg::OnOK()
{
    WCHAR	wcStr[256];
    SESSION_DATA	*pData;
    DWORD	dwIPAddr = 0;


    if (m_cBuddyURI.IsBlank())
    {   // No IP Address entered
        MessageBox ( "Please Enter an IP Address for the buddy person." );
        return;
    }

    pData = (SESSION_DATA *)GetWindowLongPtr ( ::GetWindow (m_hWnd, GW_OWNER), GWL_USERDATA);

    GetDlgItemTextW ( m_hWnd, IDC_BUDDYNAME, wcStr, 256 );

    if (wcslen (wcStr) == 0)
    {
        MessageBox ( "Please enter the Buddy Name" );
        return;
    }

    pData->bstrName = SysAllocString(_T(wcStr));


    GetDlgItemTextW ( m_hWnd, IDC_BUDDYURI, wcStr, 256 );

    if (wcslen (wcStr) == 0)
    {
        MessageBox ( "Please enter the Buddy URI" );
        return;
    }

    pData->bstrURI = SysAllocString ( _T(wcStr) );

    CDialog::OnOK();
}