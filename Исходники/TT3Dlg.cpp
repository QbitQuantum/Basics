void connlost(void *context, char *cause)
{
    CWnd *tA = theApp.GetMainWnd();

	// Disable pushbuttons
	CButton *pButton = (CButton*)tA->GetDlgItem(IDC_BUTTON1);
	pButton->EnableWindow(FALSE);
	pButton = (CButton*)tA->GetDlgItem(IDC_BUTTON2);
	pButton->EnableWindow(FALSE);
	pButton = (CButton*)tA->GetDlgItem(IDC_BUTTON3);
	pButton->EnableWindow(FALSE);
	CTT3Dlg *tA2 = (CTT3Dlg *)tA;
	tA2->MQTTConnected = FALSE;
	tA->SetDlgItemText(IDC_EDIT5, "Not connected");
	
	pMainDlg->PostMessageA(USER_1, 0, 0);
}