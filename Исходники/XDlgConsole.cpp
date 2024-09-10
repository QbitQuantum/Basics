void XDlgConsole::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CWnd *pEdit = GetDlgItem( IDC_EDIT1 );
	if( pEdit ) {
		pEdit->SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE );
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}