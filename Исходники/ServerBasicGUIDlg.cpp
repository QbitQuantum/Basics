void CServerBasicGUIDlg::OnBnClickedRunServer()
{
	if (runServer.GetCheck())
	{
		portNumber.SetReadOnly(true);
		launchServer(std::string(address), std::string(""));
	}
	else
	{
		stopServer();
		portNumber.SetReadOnly(false);
		CString simNameString;
		simNameString.LoadStringW(IDS_NOT_CONNECTED);
		simName.SetWindowText(simNameString);
	}

	if (webserverSimName() != NULL)
	{
		simName.SetWindowText(webserverSimName()->c_str());
	}

}