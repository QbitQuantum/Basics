BOOL CIBALoginDlg::OnInitDialog()
{
	CIBADialog::OnInitDialog();

	LoadImage();
	
	SetEditFont();

	InitOperatorsCombo();
	GetDlgItem(IDC_COMBO_CASHIER)->SetFont(&m_Font);
	//设置登入框的位置
	if (m_nLoginType == 0)
	{//被覆盖窗体依然处于最顶端，但失去激活
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 318, 242, SWP_NOMOVE);
		GetDlgItem(IDC_EDIT_PWD)->SetFocus();
	}
	else
	{//不做原设置，只移动新窗体
		SetWindowPos(NULL, 0, 0, 318, 242, SWP_NOMOVE);
		m_cboOperators.SetFocus();
	}

	CRgn MyRgn;
	MyRgn.CreateRoundRectRgn(0, 0, 318, 242, 12, 12);
	SetWindowRgn(MyRgn, FALSE);

	//{ 2011/09/05-8201-gxx: 
	m_btnEnmergency.ShowWindow(FALSE);
	WINDOWPLACEMENT wp;
	m_btnEnmergency.GetWindowPlacement(&wp);
	CString strAllCheckOut;
	m_btnEnmergency.GetWindowText(strAllCheckOut);
	m_btnAllCheckOut.Create( strAllCheckOut, WS_VISIBLE|WS_CHILD|SS_NOTIFY,wp.rcNormalPosition,this,IDC_BUTTON_ENMERGENCY);
	m_btnAllCheckOut.SetFont(&m_FontSmallBold);
	m_btnAllCheckOut.SetBkColor(RGB(245, 236, 216));
	m_btnAllCheckOut.SetLinkColor(RGB(218,186,129));
	m_btnAllCheckOut.SetHoverColor(RGB(235, 207, 156));
	m_btnAllCheckOut.SetVisitedColor(RGB(218, 186, 129));
	m_btnAllCheckOut.SetTransparent(FALSE);
	m_btnAllCheckOut.ShowWindow(CIBAConfig::GetInstance()->GetEnmergencyVisible());
	
	//}
	
	//m_btnEnmergency.ShowWindow(CIBAConfig::GetInstance()->GetEnmergencyVisible());

	
	//如果没有设置网吧ID或者识别码
	if (CNetBarConfig::GetInstance()->GetNetBarId() == 0 
		|| CNetBarConfig::GetInstance()->GetNetBarKey().GetLength() < 16)
	{
		CDlgNetbarConfig dlg;
		if (dlg.DoModal() == IDOK)
		{
			CNetBarConfig::GetInstance()->LoadFromDB();
		}
	}

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}