void CKademliaWnd::UpdateControlsState()
{
	if (!::IsWindow(m_hWnd))
		return;

	CString strLabel;
	if (Kademlia::CKademlia::IsConnected())
		strLabel = GetResString(IDS_MAIN_BTN_DISCONNECT);
	else if (Kademlia::CKademlia::IsRunning())
		strLabel = GetResString(IDS_MAIN_BTN_CANCEL);
	else
		strLabel = GetResString(IDS_MAIN_BTN_CONNECT);
	strLabel.Remove(_T('&'));
	GetDlgItem(IDC_KADCONNECT)->SetWindowText(strLabel);

	CString strBootstrapIP;
	GetDlgItemText(IDC_BOOTSTRAPIP, strBootstrapIP);
	CString strBootstrapPort;
	GetDlgItemText(IDC_BOOTSTRAPPORT, strBootstrapPort);
	GetDlgItem(IDC_BOOTSTRAPBUTTON)->EnableWindow(
		!Kademlia::CKademlia::IsConnected()
		&& (  (   IsDlgButtonChecked(IDC_RADIP)>0
		       && !strBootstrapIP.IsEmpty()
			   && (strBootstrapIP.Find(_T(':')) != -1 || !strBootstrapPort.IsEmpty())
			  )
		    || IsDlgButtonChecked(IDC_RADCLIENTS)>0));
}