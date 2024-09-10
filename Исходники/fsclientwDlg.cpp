void CfsclientwDlg::enableButton(const char* name, int enabled)
{
	CButton* pbut = NULL;
	if (strcmp(name, "connect") == 0)
	{
		pbut = (CButton*)GetDlgItem(IDC_BUTCONN);
		pbut->EnableWindow(enabled);
		return;
	}
	if (strcmp(name, "download") == 0)
	{
		pbut = (CButton*)GetDlgItem(IDC_BUTDW);
		pbut->EnableWindow(enabled);
		return;
	}
	if (strcmp(name, "server") == 0)
	{
		CComboBox* pcb = (CComboBox*)GetDlgItem(IDC_COMBOSRV);
		pcb->EnableWindow(enabled);
		return;
	}
}