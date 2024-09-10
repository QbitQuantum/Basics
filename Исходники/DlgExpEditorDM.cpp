BOOL CDlgExpEditorDM::OnInitDialog()
{
	// TODO:  在此添加额外的初始化

	Json::Reader jR;
	if(!jR.parse(std::string(m_strExp), m_Jv))
	{//解析失败
		EndDialog(0);
		return TRUE;
	}

	Json::Value& jStr = m_Jv["ShowRootFlag"];
	m_IsShowRoot = TRUE;
	std::string str = jStr.asString();
	if(str.empty() || str == "false")
	{
		m_IsShowRoot = FALSE;
	}

	//20140526,lc,修改为左侧树不初始化，影响加载效率，因为后期设计中已无左侧树
	m_IsInitTree = FALSE;

	m_strExp = m_Jv["OldExp"].asString().c_str();

	CDlgExpEditor::OnInitDialog();

	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON13)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON14)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON15)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON16)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON17)->ShowWindow(SW_HIDE);

	int d = 20;
	MoveItemUp(GetDlgItem(IDC_BUTTON7), GetDlgItem(IDC_EDIT_EXP), d);
	MoveItemUp(GetDlgItem(IDC_BUTTON8), GetDlgItem(IDC_EDIT_EXP), d);
	MoveItemUp(GetDlgItem(IDC_BUTTON9), GetDlgItem(IDC_EDIT_EXP), d);
	MoveItemUp(GetDlgItem(IDC_BUTTON10), GetDlgItem(IDC_EDIT_EXP), d);
	MoveItemUp(GetDlgItem(IDC_BUTTON11), GetDlgItem(IDC_EDIT_EXP), d);
	MoveItemUp(GetDlgItem(IDC_BUTTON12), GetDlgItem(IDC_EDIT_EXP), d);

	MoveItemUp(GetDlgItem(IDOK), GetDlgItem(IDC_BUTTON7), d);
	int nD= MoveItemUp(GetDlgItem(IDCANCEL), GetDlgItem(IDC_BUTTON7), d);

	CRect rect;
	GetDlgItem(IDC_STATIC_TREE)->GetWindowRect(rect);
	rect.DeflateRect(0, 0, 0, nD);
	ScreenToClient(rect);
	GetDlgItem(IDC_STATIC_TREE)->MoveWindow(rect);

	GetWindowRect(rect);
	rect.DeflateRect(0, 0, 0, nD);
	MoveWindow(rect);


	if(true)
	{//隐藏树
		CWnd& m_wndTreeLocation = *GetDlgItem(IDC_STATIC_TREE);
		m_wndGridTree.ShowWindow(SW_HIDE);
		m_wndTreeLocation.ShowWindow(SW_HIDE);
		CRect rect;
		m_wndTreeLocation.GetWindowRect(rect);
		int d = rect.Width() + 10;

		MoveItem(GetDlgItem(IDC_BUTTON7), LEFT, d);
		MoveItem(GetDlgItem(IDC_BUTTON8), LEFT, d);
		MoveItem(GetDlgItem(IDC_BUTTON9), LEFT, d);
		MoveItem(GetDlgItem(IDC_BUTTON10), LEFT, d);
		MoveItem(GetDlgItem(IDC_BUTTON11), LEFT, d);
		MoveItem(GetDlgItem(IDC_BUTTON12), LEFT, d);

		MoveItem(GetDlgItem(IDOK), LEFT, d);
		MoveItem(GetDlgItem(IDCANCEL), LEFT, d);

		MoveItem(GetDlgItem(IDC_EDIT_EXP), LEFT, d);

		GetWindowRect(rect);
		rect.DeflateRect(0, 0, d, 0);
		MoveWindow(rect);
	}

	return FALSE;
}