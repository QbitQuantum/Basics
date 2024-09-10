void CBBDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSliderCtrl * pSliderCtrl = (CSliderCtrl *)pScrollBar;
	int iID = pSliderCtrl->GetDlgCtrlID();
	int iPos = pSliderCtrl->GetPos();

	if (IDC_SLIDER_R_OFFSET == iID) {
		m_BackBalance.r_offset = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_RVALUE);
	}else if (IDC_SLIDER_G_OFFSET == iID) {
		m_BackBalance.g_offset = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_GVALUE);
	}else if (IDC_SLIDER_B_OFFSET == iID) {
		m_BackBalance.b_offset = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_BVALUE);
	}

	__super::OnHScroll(nSBCode, nPos, pScrollBar);
}