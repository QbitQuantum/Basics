void CFontTexCreaterDlg::OnBnClickedBrowseTxt()
{
	CFileDialog dlg( TRUE , _T("txt") ) ;

	if( dlg.DoModal() == IDOK )
	{
		CString path = dlg.GetPathName() ;

		if( path.GetLength() > 3 )
		{
			CEdit* pEdt = (CEdit*)GetDlgItem(IDC_EDT_TXT) ;

			if( pEdt )
				pEdt->SetWindowTextW( path.GetBuffer() ) ;
		}
	}

	ResetDir() ;
}