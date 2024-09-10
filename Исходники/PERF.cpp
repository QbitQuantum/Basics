void PERF::OnBnClickedOk()
{
	CTT3App *tA    = (CTT3App*)theApp.GetMainWnd();
	CTT3Dlg *pW    = (CTT3Dlg*)tA;
	pW->iPerfPub   = GetDlgItemInt(IDC_EDIT1, 0, FALSE);
	pW->iDelay     = GetDlgItemInt(IDC_EDIT2, 0, FALSE);
	pW->iTT3Apps   = GetDlgItemInt(IDC_EDIT4, 0, FALSE);
	GetDlgItemTextA(IDC_EDIT5, pW->sTT3Subscribe, 100);

	CDialog::OnOK();
}