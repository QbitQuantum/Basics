void CPassWordDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	int n = display.GetLength();
	
	if (n >= 4)					//提示信息，则先清空
	{
		display = CString("");
	}
	
	display += CString("*");	//键盘输入一位密码
	input += CString("1");
	n ++;						//长度加一

	if (n == 4)					//输入满四位，判断密码是否正确
	{
		if (input == password)
		{
			CPublic::NumFlag = FALSE;
			this->EndDialog(0);
			CKeyBoardDlg *pKeyBoardDlg = new CKeyBoardDlg;
			pKeyBoardDlg->Create(IDD_KeyBoard, this);
			pKeyBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			display = CString("密码错误，请重新输入密码");
			input = CString("");
		}
	}
	
	UpdateData(FALSE);
}