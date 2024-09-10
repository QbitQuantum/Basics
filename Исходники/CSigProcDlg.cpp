SIGPROCDLG_API void CSigProcDlg::SetEditSig(const char *strIn)
{
	SetDlgItemText(IDC_SIG, strIn);
	sigstr = strIn;
	UpdateWindow(hDlg);
}