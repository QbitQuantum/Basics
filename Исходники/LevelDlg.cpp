// 초기값
BOOL CLevelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_COLOR);
	pStatic->GetWindowRect(&ld_rect);
	ScreenToClient(&ld_rect);
	
	// 리스트박스의 초기값 설정
	ld_cFont.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
}