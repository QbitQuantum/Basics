//为验证码输入框设置输入焦点
void COcrInput::FocusOcrInput(void)
{
 	ASSERT(m_pfuncSetOcrInputFocus != NULL);
 
	if (m_pfuncSetOcrInputFocus())
 	{
		return;
 	}

	HWND hWndDlg = FindWindow(_T("#32770"), _T("验证码输入"));
	HWND hWndInputDlg = NULL;
	HWND hInputControl = NULL;

	do 
	{
		if (!hWndDlg)
		{
			return;
		}
			
		//找到单个验证码输入对话框
		hWndInputDlg = FindWindowEx(hWndDlg, NULL, _T("#32770"), NULL);
		if (hWndInputDlg)
		{	
			SwitchToThisWindow(hWndInputDlg, TRUE);
			//找到输入框
			hInputControl = FindWindowEx(hWndInputDlg, NULL, _T("Edit"), NULL);
			if (hInputControl) 
				SendMessage(hInputControl, WM_SETFOCUS, NULL, NULL);
		}

		hWndDlg = FindWindowEx(NULL, hWndDlg, _T("#32770"), _T("验证码输入"));
	} while (true);

}