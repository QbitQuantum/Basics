void CNamePage::OnUseName()
{
	// enable the edit control and move to it....
	CWnd* pwndEdit = GetDlgItem( IDC_SVRNAME );
	if ( pwndEdit )
	{
		pwndEdit->EnableWindow( TRUE );
		pwndEdit->SetFocus();
	}
}