BOOL CDLStateDlg::OnInitDialog ()
{
    CDialog::OnInitDialog ();
    //set the help id for context sensitive help
    SetWindowContextHelpId(IDD);
    PrepareList ();
    m_Details.EnableWindow (m_iSelection != -1);
    return (TRUE);  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}