BOOL CDialog_Check::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_checkModal)
	{
		SetWindowText(_T("入库"));
	}
	else
	{
		SetWindowText(_T("出库"));
	}

	InitComobox();

	if(!m_date.GetId().empty())
	{
		m_date.m_material = m_allMaterial.at(m_mName_ctrl.GetCurSel());
		int index = 0;
		for (index = 0; index < m_allMaterial.size();index ++)
			if (m_allMaterial[index].GetId() == m_date.GetId())
				break;
		m_mName_ctrl.SetCurSel(index);
		char cTmp[20] ={0};
		itoa(m_date.m_num,cTmp,10);
		m_mNum_ctrl.SetWindowText(m_dateChange.stringToCstring(string(cTmp)));
		memset(cTmp,0,20);
		ltoa(m_date.m_total,cTmp,10);
		m_total_ctrl.SetWindowText(m_dateChange.stringToCstring(string(cTmp)));
		for(index = 0;index<m_allClass.size();index ++)
			if(m_allClass[index].GetId() == m_date.m_class.GetId())
				break;
		m_cName_ctrl.SetCurSel(index);
		m_wName_ctrl.SetWindowText(m_date.m_operateWare);
		for (index = 0;index <m_allUser.size();index ++)
			if (m_allUser[index].GetId() == m_date.m_userInfo.GetId())
				break;
		m_pName_ctrl.SetCurSel(index);
		m_telPhone_ctrl.SetWindowText(m_date.m_tellPhone);
		m_detail_ctrl.SetWindowText(m_date.m_detail);
	}

	m_wName_ctrl.SetWindowText(CControl_bace::s_wareHouse.m_aname);
	return TRUE;
}