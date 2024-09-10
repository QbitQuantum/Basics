void CFusicSettingsAccessGroupsDlg::OnBnClickedOk()
{
	//Ensure the user has added some access groups:
	if(g_vecAG.size() == 0)
	{
		MessageBox("Please enter some LDAP access groups.", "Fusic Settings",
			MB_OK | MB_ICONINFORMATION);
		return;
	}

	//get the app:
	CFusicApp* theApp = (CFusicApp*)AfxGetApp();

	//concaternate the accessgroups string:
	CString strAccessGroups;

	for(std::vector<CString>::iterator i = g_vecAG.begin();
		i != g_vecAG.end(); i++)
	{
		strAccessGroups += (*i);
		strAccessGroups += ";";
	}

	//write out the string:
	theApp->WriteProfileStringA("LDAP Settings", "AccessGroups", strAccessGroups);

	//all done.
	OnOK();
}