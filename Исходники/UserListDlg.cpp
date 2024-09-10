void CUserListDlg::OnSize( UINT nType, int cx, int cy ) {
	CDialog::OnSize( nType, cx, cy );
	CListBox* userList = (CListBox*)GetDlgItem( IDC_USERLIST );
	CButton* newButton = (CButton*)GetDlgItem( IDC_NEWUSERBUTTON );
	CButton* deleteButton = (CButton*)GetDlgItem( IDC_DELETEUSERBUTTON );
	if ( userList && newButton && deleteButton ) {
		CRect client;
		GetClientRect( client );

		CRect button;
		newButton->CButton::GetWindowRect( button );

		userList->MoveWindow( 0, 0, client.Width(), client.Height()-button.Height() );
		newButton->MoveWindow( 0, client.Height()-button.Height(), client.Width()/2, button.Height() );
		deleteButton->MoveWindow( client.Width()/2, client.Height()-button.Height(), client.Width()/2, button.Height() );
	}
}