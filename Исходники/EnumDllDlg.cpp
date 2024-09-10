BOOL CEnumDllDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	m_list.GetWindowRect(&rect);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, _T("DLL名"), LVCFMT_LEFT, rect.Width() / 5, 0);
	m_list.InsertColumn(1, _T("DLL路径"), LVCFMT_LEFT, 15 * rect.Width() / 20, 1);
	MODULEENTRY32 module = { 0 };
	module.dwSize = sizeof(MODULEENTRY32);
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_pID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		BOOL ret = Module32First(hSnap, &module);
		int item = 0;
		CString s;
		while (ret)
		{
			m_list.InsertItem(item, module.szModule);
			m_list.SetItemText(item, 1, module.szExePath);
			++item;
			ret = Module32Next(hSnap, &module);
		}
		CloseHandle(hSnap);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}