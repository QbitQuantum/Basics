void CRegisterMonitorDlg::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	if(!m_port_open)
		MessageBox(_T("Please Open the Com port"));
	UpdateData(TRUE);

	sel_item=m_combo_reg.GetCurSel();
	CString temp_cs;
	switch(sel_item)
	{
	case 0:
		temp_cs.Format(_T("%d"),m_reg_address1);
		write_register = m_reg_address1;
		break;
	case 1:
		temp_cs.Format(_T("%d"),m_reg_address2);
		write_register = m_reg_address2;
		break;
	case 2:
		temp_cs.Format(_T("%d"),m_reg_address3);
		write_register = m_reg_address3;
		break;
	case 3:
		temp_cs.Format(_T("%d"),m_reg_address4);
		write_register = m_reg_address4;
		break;
	case 4:
		temp_cs.Format(_T("%d"),m_reg_address5);
		write_register = m_reg_address5;
		break;
	default:
		break;
	}

	SetDlgItemTextW(IDC_EDIT_WRITE,_T(""));

	SetDlgItemTextW(IDC_STATIC_REGISTER_WRITE,temp_cs);

	CString cs_write;
	GetDlgItemTextW(IDC_EDIT_WRITE,cs_write.GetBuffer(MAX_PATH),MAX_PATH);
	cs_write.ReleaseBuffer();
	write_value = _wtoi(cs_write);

	//if(hWriteThread==NULL)


}