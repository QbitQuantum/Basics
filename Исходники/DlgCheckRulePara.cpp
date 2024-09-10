// 更新过滤数据
BOOL CDlgCheckRulePara::UpdateFilterControlByCheckRule(const CheckRule &checkRule)
{
	CStringArray arrMdlFilterCheckRule;//模型筛选
	CStringToCStringArray(checkRule.strRuleName, arrMdlFilterCheckRule);
	int nArrSize = (int)arrMdlFilterCheckRule.GetSize();
	if (nArrSize < 3 || arrMdlFilterCheckRule.GetAt(0).CompareNoCase(L"filter") != 0)
		return FALSE;

	m_cmbFilterCategory.ResetContent();
	m_cmbFilterCategory.AddString(L"模型名");
	m_cmbFilterCategory.AddString(L"公用名称");
	m_cmbFilterCategory.AddString(L"参数");

	m_cmbFilterParaName.ResetContent();

	int ntag = -1;
	CString strCatagory = arrMdlFilterCheckRule.GetAt(1);
	if (strCatagory.CompareNoCase(L"name") == 0)
	{
		ntag = 0;
		m_cmbFilterParaName.EnableWindow(FALSE);
	}
	else if (strCatagory.CompareNoCase(L"common_name") == 0)
	{
		ntag = 1;
		m_cmbFilterParaName.EnableWindow(FALSE);
	}
	else if (strCatagory.CompareNoCase(L"parameter") == 0)
	{
		ntag = 2;
		m_cmbFilterParaName.EnableWindow(TRUE);
		m_strParaParameter = arrMdlFilterCheckRule.GetAt(2);//参数名静态变量赋值
	}
	else
		return TRUE;

	m_cmbFilterCategory.SetCurSel(ntag);

	if (ntag == 2)
	{
		CString strParaContent = arrMdlFilterCheckRule.GetAt(2);
		int nFind = -1;
		for (int i = 0; i < theApp.m_arrMdlParam.GetSize(); i++)
		{
			m_cmbFilterParaName.AddString(theApp.m_arrMdlParam[i]);
			if (strParaContent.CompareNoCase(theApp.m_arrMdlParam[i]) == 0)
			{
				nFind = i;
			}
		}
		if (nFind >= 0)
			m_cmbFilterParaName.SetCurSel(nFind);
		else
			m_cmbFilterParaName.SetWindowText(strParaContent);
	}

	if (arrMdlFilterCheckRule.GetSize() == 3)
		m_strFilterContent = arrMdlFilterCheckRule.GetAt(2);
	else
		m_strFilterContent = arrMdlFilterCheckRule.GetAt(3);

	if (arrMdlFilterCheckRule.GetSize() > 4)
		m_bMdlFilter = _wtoi(arrMdlFilterCheckRule.GetAt(4));
	if (m_bMdlFilter)
	{
		m_cmbFilterCategory.EnableWindow(TRUE);
		int nIndex = m_cmbFilterCategory.GetCurSel();
		if (nIndex == 0)
			m_cmbFilterParaName.EnableWindow(FALSE);
		else if (nIndex == 1)
			m_cmbFilterParaName.EnableWindow(FALSE);
		else
			m_cmbFilterParaName.EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MDL_PARA_CATA_CONTENT)->EnableWindow(TRUE);
	}
	else
	{
		m_cmbFilterCategory.EnableWindow(FALSE);
		m_cmbFilterParaName.EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MDL_PARA_CATA_CONTENT)->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
	return TRUE;
}