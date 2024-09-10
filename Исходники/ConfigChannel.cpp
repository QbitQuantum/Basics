void CConfigChannel::OnSelchangeComboOsd() 
{
	if (!m_bInited || m_chnIdx < 0)
	{
		return;
	}

	//store current osd config
	if (m_osdIdx >= 0)
	{
		//later
	}

	//show new one
	int osdIdx = m_osdsel.GetCurSel();
	if (osdIdx < 0)
	{
		return;
	}
	m_osdIdx = osdIdx;

	switch(osdIdx) 
	{
	case 0: // channel name osd
		m_osdshowchk.SetCheck(m_chnCFG[m_chnIdx].stChannelOSD.bShow);
		SetDlgItemInt(IDC_EDIT_FORE_RED, m_chnCFG[m_chnIdx].stChannelOSD.rgbaFrontground & 0xFF);
		SetDlgItemInt(IDC_EDIT_FORE_GREEN, (m_chnCFG[m_chnIdx].stChannelOSD.rgbaFrontground>>8) & 0xFF);
		SetDlgItemInt(IDC_EDIT_FORE_BLUE, (m_chnCFG[m_chnIdx].stChannelOSD.rgbaFrontground>>16) & 0xFF);
		SetDlgItemInt(IDC_EDIT_FORE_TRANS, (m_chnCFG[m_chnIdx].stChannelOSD.rgbaFrontground>>24) & 0xFF);

		SetDlgItemInt(IDC_EDIT_BACK_RED, m_chnCFG[m_chnIdx].stChannelOSD.rgbaBackground & 0xFF);
		SetDlgItemInt(IDC_EDIT_BACK_GREEN, (m_chnCFG[m_chnIdx].stChannelOSD.rgbaBackground>>8) & 0xFF);
		SetDlgItemInt(IDC_EDIT_BACK_BLUE, (m_chnCFG[m_chnIdx].stChannelOSD.rgbaBackground>>16) & 0xFF);
		SetDlgItemInt(IDC_EDIT_BACK_TRANS, (m_chnCFG[m_chnIdx].stChannelOSD.rgbaBackground>>24) & 0xFF);

		SetDlgItemInt(IDC_EDIT_RECT_LFET, m_chnCFG[m_chnIdx].stChannelOSD.rcRect.left & 0xFF);
		SetDlgItemInt(IDC_EDIT_RECT_TOP, (m_chnCFG[m_chnIdx].stChannelOSD.rcRect.top>>8) & 0xFF);
		SetDlgItemInt(IDC_EDIT_RECT_RIGHT, (m_chnCFG[m_chnIdx].stChannelOSD.rcRect.right>>16) & 0xFF);
		SetDlgItemInt(IDC_EDIT_RECT_BOTTOM, (m_chnCFG[m_chnIdx].stChannelOSD.rcRect.bottom>>24) & 0xFF);

		GetDlgItem(IDC_STATIC_BLINDTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_BLINDTYPE)->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_osdshowchk.SetCheck(m_chnCFG[m_chnIdx].stChannelOSD.bShow);
		SetDlgItemInt(IDC_EDIT_FORE_RED, m_chnCFG[m_chnIdx].stTimeOSD.rgbaFrontground & 0xFF);
		SetDlgItemInt(IDC_EDIT_FORE_GREEN, (m_chnCFG[m_chnIdx].stTimeOSD.rgbaFrontground>>8) & 0xFF);
		SetDlgItemInt(IDC_EDIT_FORE_BLUE, (m_chnCFG[m_chnIdx].stTimeOSD.rgbaFrontground>>16) & 0xFF);
		SetDlgItemInt(IDC_EDIT_FORE_TRANS, (m_chnCFG[m_chnIdx].stTimeOSD.rgbaFrontground>>24) & 0xFF);
		
		SetDlgItemInt(IDC_EDIT_BACK_RED, m_chnCFG[m_chnIdx].stTimeOSD.rgbaBackground & 0xFF);
		SetDlgItemInt(IDC_EDIT_BACK_GREEN, (m_chnCFG[m_chnIdx].stTimeOSD.rgbaBackground>>8) & 0xFF);
		SetDlgItemInt(IDC_EDIT_BACK_BLUE, (m_chnCFG[m_chnIdx].stTimeOSD.rgbaBackground>>16) & 0xFF);
		SetDlgItemInt(IDC_EDIT_BACK_TRANS, (m_chnCFG[m_chnIdx].stTimeOSD.rgbaBackground>>24) & 0xFF);
		
		SetDlgItemInt(IDC_EDIT_RECT_LFET, m_chnCFG[m_chnIdx].stTimeOSD.rcRect.left & 0xFF);
		SetDlgItemInt(IDC_EDIT_RECT_TOP, (m_chnCFG[m_chnIdx].stTimeOSD.rcRect.top>>8) & 0xFF);
		SetDlgItemInt(IDC_EDIT_RECT_RIGHT, (m_chnCFG[m_chnIdx].stTimeOSD.rcRect.right>>16) & 0xFF);
		SetDlgItemInt(IDC_EDIT_RECT_BOTTOM, (m_chnCFG[m_chnIdx].stTimeOSD.rcRect.bottom>>24) & 0xFF);

		GetDlgItem(IDC_STATIC_BLINDTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_BLINDTYPE)->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_osdshowchk.SetCheck(m_chnCFG[m_chnIdx].stChannelOSD.bShow);
		SetDlgItemInt(IDC_EDIT_FORE_RED, m_chnCFG[m_chnIdx].stBlindCover[0].rgbaFrontground & 0xFF);
		SetDlgItemInt(IDC_EDIT_FORE_GREEN, (m_chnCFG[m_chnIdx].stBlindCover[0].rgbaFrontground>>8) & 0xFF);
		SetDlgItemInt(IDC_EDIT_FORE_BLUE, (m_chnCFG[m_chnIdx].stBlindCover[0].rgbaFrontground>>16) & 0xFF);
		SetDlgItemInt(IDC_EDIT_FORE_TRANS, (m_chnCFG[m_chnIdx].stBlindCover[0].rgbaFrontground>>24) & 0xFF);
		
		SetDlgItemInt(IDC_EDIT_BACK_RED, m_chnCFG[m_chnIdx].stBlindCover[0].rgbaBackground & 0xFF);
		SetDlgItemInt(IDC_EDIT_BACK_GREEN, (m_chnCFG[m_chnIdx].stBlindCover[0].rgbaBackground>>8) & 0xFF);
		SetDlgItemInt(IDC_EDIT_BACK_BLUE, (m_chnCFG[m_chnIdx].stBlindCover[0].rgbaBackground>>16) & 0xFF);
		SetDlgItemInt(IDC_EDIT_BACK_TRANS, (m_chnCFG[m_chnIdx].stBlindCover[0].rgbaBackground>>24) & 0xFF);
		
		SetDlgItemInt(IDC_EDIT_RECT_LFET, m_chnCFG[m_chnIdx].stBlindCover[0].rcRect.left & 0xFF);
		SetDlgItemInt(IDC_EDIT_RECT_TOP, (m_chnCFG[m_chnIdx].stBlindCover[0].rcRect.top>>8) & 0xFF);
		SetDlgItemInt(IDC_EDIT_RECT_RIGHT, (m_chnCFG[m_chnIdx].stBlindCover[0].rcRect.right>>16) & 0xFF);
		SetDlgItemInt(IDC_EDIT_RECT_BOTTOM, (m_chnCFG[m_chnIdx].stBlindCover[0].rcRect.bottom>>24) & 0xFF);		

		m_blindtypesel.SetCurSel(m_chnCFG[m_chnIdx].byBlindEnable);

		GetDlgItem(IDC_STATIC_BLINDTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_BLINDTYPE)->ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	
}