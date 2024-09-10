BOOL CMSDNIntegratorDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // Since we are using a progress control, set the progress
    // control for the integration.
    m_MSDNIntegrate.SetProgressCtrl(&m_progress);

    if ( m_strEditTitle.IsEmpty() )
        m_strEditTitle = _T("<Enter a title for your collection>");

    if ( m_strEditID.IsEmpty() )
        m_strEditID    = _T("<Enter a unique ID for your collection>");

    // Set the integrator defaults.
    m_MSDNIntegrate.SetTitleString(m_strEditTitle);
    m_MSDNIntegrate.SetUniqueID(m_strEditID);
    m_MSDNIntegrate.SetHelpVer(m_strEditVer);

    UpdateData(FALSE);
    return TRUE;  // return TRUE  unless you set the focus to a control
}