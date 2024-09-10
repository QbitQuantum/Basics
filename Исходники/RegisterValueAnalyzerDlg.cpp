void CRegisterValueAnalyzerDlg::OnBnClickedAxisscrollbarCheck()
{
	CChartAxis* pAxis = GetSelectedAxis();
	bool bShow = ((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->GetCheck() == 1;
	pAxis->EnableScrollBar(bShow);
}