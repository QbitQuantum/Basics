void CRegDlg::OnBnClickedOk()
{
	CString m_regNo, m_Marchine;
	GetDlgItem(IDC_EDIT_REG)->GetWindowText(m_regNo);
	GetDlgItem(IDC_EDIT_MATCHIN)->GetWindowText(m_Marchine);

	if (m_regNo.IsEmpty())
	{
		MessageBox(_T("ÇëÊäÈë×¢²áÂë!"),_T("EtermServer·þÎñ¶Ë×¢²á"),MB_OK|MB_ICONEXCLAMATION);
		GetDlgItem(IDC_EDIT_MATCHIN)->SetFocus();
		return;
	}

	USES_CONVERSION;

	Encrypt encrypt;
	unsigned char key[] = "&feghtyj";
	CString strValid = CString(A2T(encrypt.decrypt(key, (char*)T2A(m_regNo))));

	if (m_Marchine == strValid)
	{
		CRegistry reg(HKEY_LOCAL_MACHINE);
		BOOL bRet = reg.Open(_T("SOFTWARE\0"));
		if (bRet)
		{
			BOOL bRet = reg.Open(_T("EtermServer\0"));
			if (!bRet)
				bRet = reg.CreateKey(_T("EtermServer"));
			bRet = reg.Open(_T("Register\0"));
			if (!bRet)
				bRet = reg.CreateKey(_T("Register"));
			bRet = reg.Write(_T(""), m_regNo);

			if (bRet)
			{
				MessageBox(_T("×¢²á³É¹¦!"), _T("EtermServer·þÎñ¶Ë×¢²á"), MB_OK | MB_ICONINFORMATION);
				CDialogEx::OnOK();
			}
		}
		if (!bRet)
		{
			FILE* file = NULL;
			TCHAR szFile[1024] = { 0 };
			_stprintf_s(szFile, _T("%s\\register.dat"), Global::szAppPath);
			errno_t no = _tfopen_s(&file, szFile, _T("w"));
			if (no == 0)
			{
				char szBuf[1024] = { 0 };
				fputs(CT2A(m_regNo), file);
				fclose(file);

				MessageBox(_T("×¢²á³É¹¦!"), _T("EtermServer·þÎñ¶Ë×¢²á"), MB_OK | MB_ICONINFORMATION);
				CDialogEx::OnOK();			
			}
			else
			{
				MessageBox(_T("×¢²áÊ§°Ü!"), _T("EtermServer·þÎñ¶Ë×¢²á"), MB_OK | MB_ICONEXCLAMATION);
			}
		}
	}
	else
	{
		MessageBox(_T("×¢²áÊ§°Ü!"), _T("EtermServer·þÎñ¶Ë×¢²á"), MB_OK | MB_ICONEXCLAMATION);
	}
}