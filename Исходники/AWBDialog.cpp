void CAWBDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (nSBCode != SB_ENDSCROLL) {
		//CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
		//return;
	//}

	CSliderCtrl * pSliderCtrl = (CSliderCtrl *)pScrollBar;
	int iID = pSliderCtrl->GetDlgCtrlID();
	int iPos = pSliderCtrl->GetPos();


	int nIndex, num;
	CString GroupValue;

	nIndex = m_ComGroupValue.GetCurSel();
	m_ComGroupValue.GetLBText(nIndex, GroupValue);
	num = _ttoi(GroupValue);

again:
	if (IDC_SLIDER_RHIGH == iID) {
		m_stAwbInfo[num].r_high = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_RH_VAL);
	}else if (IDC_SLIDER_RLOW == iID) {
		m_stAwbInfo[num].r_low = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_RL_VAL);
	}else if (IDC_SLIDER_GHIGH == iID) {
		m_stAwbInfo[num].g_high = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_GH_VAL);
	}else if (IDC_SLIDER_GLOW == iID) {
		m_stAwbInfo[num].g_low = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_GL_VAL);
	}else if (IDC_SLIDER_BHIGH == iID) {
		m_stAwbInfo[num].b_high = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_BH_VAL);
	}else if (IDC_SLIDER_BLOW == iID) {
		m_stAwbInfo[num].b_low = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_BL_VAL);
	}else if (IDC_SLIDER_RGBHIGH == iID) {
		m_stAwbInfo[num].grb_high = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_RGBH_VAL);
	}else if (IDC_SLIDER_RGBLOW == iID) {
		m_stAwbInfo[num].grb_low = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_RGBL_VAL);
	}else if (IDC_SLIDER_GRHIGH == iID) {
		m_stAwbInfo[num].gr_high = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_GRH_VAL);
	}else if (IDC_SLIDER_GRLOW == iID) {
		m_stAwbInfo[num].gr_low = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_GRL_VAL);
	}else if (IDC_SLIDER_GBHIGH == iID) {
		m_stAwbInfo[num].gb_high = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_GBH_VAL);
	}else if (IDC_SLIDER_GBLOW == iID) {
		m_stAwbInfo[num].gb_low = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_GBL_VAL);
	}else {
		fprintf(stderr, "AWB page Unknown slider ID(%d)\n", iID);
	}
	
	if (JudgeHighLow(iID, iPos) == 1) {
		(pSliderCtrl = ((CSliderCtrl *)GetDlgItem(iID)))->SetPos(iPos);
		goto again;
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}