void CDemosaicDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSliderCtrl * pSliderCtrl = (CSliderCtrl *)pScrollBar;
	int iID = pSliderCtrl->GetDlgCtrlID();
	int iPos = pSliderCtrl->GetPos();

	if (IDC_SLIDER_THRESOLD == iID) {
		m_Demosaic.threshold = iPos;
		ProcessStaticText(pSliderCtrl, IDC_STATIC_THRESOLD_VAL);
	}

	__super::OnHScroll(nSBCode, nPos, pScrollBar);
}