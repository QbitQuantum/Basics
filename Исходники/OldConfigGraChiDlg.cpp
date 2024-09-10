//销毁编辑框//
void COldConfigGraChiDlg::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
	CString strEditData;
	distroyedit->GetWindowText(strEditData);
	strEditData = strEditData.Trim();

	if (strEditData.IsEmpty())             //如果输入为空，则销毁编辑框//
	{
		distroyedit->DestroyWindow();
		if (m_vectConfigPara[Item].m_DefaultValue!=-3001)
		{
			m_vectConfigPara[Item].m_DefaultValue = -3001;
			m_bIsParaValueChange = true;
		}
		list->SetItemText(Item, 3, _T(""));
		return;
	}
	if (strEditData == strEditData.SpanIncluding(_T("0123456789.")))
	{
		float tempfloat = (float)_wtof(strEditData);
		strEditData.Format(_T("%.2f"), tempfloat);
		list->SetItemText(Item, 3, strEditData);                 //将修改写入列表框//
		if (tempfloat != m_vectConfigPara[Item].m_DefaultValue)  //判断值是否发生了变化//
		{
			m_vectConfigPara[Item].m_DefaultValue = tempfloat;    //将修改后的值存入容器//
			m_bIsParaValueChange = true;
		}
		
	}
	else
		AfxMessageBox(_T("非法操作，请输入数字！"));
	distroyedit->DestroyWindow();                          //销毁对象//
}