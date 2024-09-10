void CControlTestDialog::OnBnClickedButtonTestCheckPushButton()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ResetTest();

	CCheckButton *pBtn = new CCheckButton();

	m_pTestWnd = pBtn;

	CRect rcClient;
	this->GetClientRect( rcClient );
	const CRect rcSt( 20,120, rcClient.Width()-20, 160 );

	pBtn->Create( _T( "复选按钮测试" ), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE , rcSt, this, 1000 );

	//tstring strAppDir = ParsePath( GetModulePath().c_str() ).m_strDirectory;

	//tstring  strLogoPath= strAppDir + _T( "res\\chs\\btn_login.jpg" );
	//pBtn->SetImage( strLogoPath.c_str(), strLogoPath.c_str() );

	//pBtn->SetTransparentMask( TRUE, RGB( 255,0,255) );

	pBtn->ShowWindow( SW_SHOW );
}