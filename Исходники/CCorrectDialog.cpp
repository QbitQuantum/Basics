void CCCorrectDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (nSBCode != SB_ENDSCROLL) {
		//CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
		//return;
	//}

	CSliderCtrl * pSliderCtrl = (CSliderCtrl *)pScrollBar;
	int iID = pSliderCtrl->GetDlgCtrlID();
	int iPos = pSliderCtrl->GetPos();

again:
	if (IDC_SLIDER_C11 == iID) {
		m_CCorrect.ccMtrx[0][0] = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_C11_VAL);
	}else if (IDC_SLIDER_C12 == iID) {
		m_CCorrect.ccMtrx[0][1] = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_C12_VAL);
	}else if (IDC_SLIDER_C13 == iID) {
		m_CCorrect.ccMtrx[0][2] = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_C13_VAL);
	}else if (IDC_SLIDER_C21 == iID) {
		m_CCorrect.ccMtrx[1][0] = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_C21_VAL);
	}else if (IDC_SLIDER_C22 == iID) {
		m_CCorrect.ccMtrx[1][1] = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_C22_VAL);
	}else if (IDC_SLIDER_C23 == iID) {
		m_CCorrect.ccMtrx[1][2] = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_C23_VAL);
	}else if (IDC_SLIDER_C31 == iID) {
		m_CCorrect.ccMtrx[2][0] = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_C31_VAL);
	}else if (IDC_SLIDER_C32 == iID) {
		m_CCorrect.ccMtrx[2][1] = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_C32_VAL);
	}else if (IDC_SLIDER_C33 == iID) {
		m_CCorrect.ccMtrx[2][2] = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_C33_VAL);
	}else if (IDC_SLIDER_ILOW == iID) {
		m_CCorrect.cc_thrs_low = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_ILOW_VAL);
	}else if (IDC_SLIDER_IHIGH == iID) {
		m_CCorrect.cc_thrs_high = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_IHIGH_VAL);
	}

	if (JudgeHighLow(iID, iPos) == 1) {
		(pSliderCtrl = ((CSliderCtrl *)GetDlgItem(iID)))->SetPos(iPos);
		goto again;
	}

	__super::OnHScroll(nSBCode, nPos, pScrollBar);
}