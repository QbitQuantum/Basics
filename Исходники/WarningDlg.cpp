/* #FN#
   Performs special processing when the dialog box is initialized */
BOOL
/* #AS#
   TRUE unless you set the focus to a control */
CWarningDlg::
OnInitDialog()
{
	CDialog::OnInitDialog();

	if( !m_bCancel )
	{
		CRect rcCtrl;

		CButton *pButton = (CButton *)GetDlgItem( IDCANCEL );
		ASSERT(NULL != pButton);

		pButton->GetWindowRect( rcCtrl );
		ScreenToClient( rcCtrl );
		pButton->ShowWindow( SW_HIDE );

		pButton = (CButton *)GetDlgItem( IDOK );
		ASSERT(NULL != pButton);

		pButton->SetWindowPos( NULL,
			rcCtrl.TopLeft().x,
			rcCtrl.TopLeft().y,
			0, 0,
			SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS );
	}

	if( '\0' == *m_szWarningText )
		_LoadStringLx( -1 != m_nWarningID ? m_nWarningID : IDS_WARN_ERROR, m_szWarningText );

	SetDlgItemText( IDC_WARNING_TEXT, m_szWarningText );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
} /* #OF# CWarningDlg::OnInitDialog */