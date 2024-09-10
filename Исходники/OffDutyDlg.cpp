//设置统计的字体
void CDlgIBADuty::SetStaticFont()
{
	CWnd* pChildWnd = GetWindow(GW_CHILD);   

	while (pChildWnd != NULL)   
	{
		TCHAR szClassName[MAX_PATH] = {0};
		GetClassName(pChildWnd->GetSafeHwnd(), szClassName, MAX_PATH);

		if (lstrcmp(szClassName, _T("Static")) == 0)
		{
			switch(pChildWnd->GetDlgCtrlID())
			{
			case IDC_STATIC_CREDIT:
			case IDC_STATIC_RETURNED:
			case IDC_STATIC_CASHPAY:
			case IDC_STATIC_DIANKA:
			case IDC_STATIC_STOREIN:
			case IDC_STATIC_DEPOSIT:
			case IDC_STATIC_NETCASH:
			case IDC_STATIC_RESERVE:
			case IDC_STATIC_SELFDUTY:
			case IDC_STATIC_CREDITCARD:
			case IDC_STATIC_NETBARPAY:
			case IDC_STATIC_ZSB_CONSUME:
			case IDC_STATIC_ZSB_BALANCE:
				GetDlgItem(pChildWnd->GetDlgCtrlID())->SetFont(&m_Font);
				break;

			}
			if (pChildWnd->GetDlgCtrlID() != IDC_STATIC && 
				pChildWnd->GetDlgCtrlID() != IDC_STATIC2_HANDLEIN && 
				pChildWnd->GetDlgCtrlID() != IDC_STATIC2_NEXTRESERVE)
			{
				//GetDlgItem(pChildWnd->GetDlgCtrlID())->SetFont(&m_Font);
			}
		}
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);  
	}
}