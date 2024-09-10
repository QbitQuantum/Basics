void CCustom1Dlg::EnableCheckboxes()
{
	CWnd* pConsoleApp = GetDlgItem(IDC_CHECK_CONSOLE_APP);
	CWnd* pPublishImport = GetDlgItem(IDC_CHECK_PUBLISH_IMPORT);
	CWnd* pImportLib = GetDlgItem(IDC_EDIT_IMPLIB_PATH);
	switch (m_ProjectType)
	{
	case 0:
		pConsoleApp->EnableWindow( false );
		pPublishImport->EnableWindow( false );
		pImportLib->EnableWindow( false );
		break;

	case 1:
		pConsoleApp->EnableWindow( false );
		pPublishImport->EnableWindow( true );
		pImportLib->EnableWindow( m_PublishImportLib );
		break;

	case 2:
		pConsoleApp->EnableWindow( true );
		pPublishImport->EnableWindow( false );
		pImportLib->EnableWindow( false );
		break;
	}
}