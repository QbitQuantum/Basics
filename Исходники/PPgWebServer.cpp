BOOL CPPgWebServer::OnApply()
{	
	if(m_bModified)
	{
		CString sBuf;

		// get and check templatefile existance...
		GetDlgItem(IDC_TMPLPATH)->GetWindowText(sBuf);
		if ( IsDlgButtonChecked(IDC_WSENABLED) && !PathFileExists(sBuf)) {
			CString buffer;
			buffer.Format(GetResString(IDS_WEB_ERR_CANTLOAD),sBuf);
			AfxMessageBox(buffer,MB_OK);
			return FALSE;
		}
		thePrefs.SetTemplate(sBuf);
		theApp.webserver->ReloadTemplates();


		uint16 oldPort=thePrefs.GetWSPort();

		GetDlgItem(IDC_WSPASS)->GetWindowText(sBuf);
		if(sBuf != HIDDEN_PASSWORD)
			thePrefs.SetWSPass(sBuf);
		
		GetDlgItem(IDC_WSPASSLOW)->GetWindowText(sBuf);
		if(sBuf != HIDDEN_PASSWORD)
			thePrefs.SetWSLowPass(sBuf);

		GetDlgItem(IDC_WSPORT)->GetWindowText(sBuf);
		if (_tstoi(sBuf)!=oldPort) {
			thePrefs.SetWSPort((uint16)_tstoi(sBuf));
			theApp.webserver->RestartServer();
		}

		GetDlgItemText(IDC_WSTIMEOUT,sBuf);
		thePrefs.m_iWebTimeoutMins=_tstoi(sBuf);

		thePrefs.SetWSIsEnabled(IsDlgButtonChecked(IDC_WSENABLED)!=0);
		thePrefs.SetWSIsLowUserEnabled(IsDlgButtonChecked(IDC_WSENABLEDLOW)!=0);
		thePrefs.SetWebUseGzip(IsDlgButtonChecked(IDC_WS_GZIP)!=0);
		theApp.webserver->StartServer();
		thePrefs.m_bAllowAdminHiLevFunc= (IsDlgButtonChecked(IDC_WS_ALLOWHILEVFUNC)!=0);

		// mobilemule
		GetDlgItem(IDC_MMPORT_FIELD)->GetWindowText(sBuf);
		if (_tstoi(sBuf)!= thePrefs.GetMMPort() ) {
			thePrefs.SetMMPort((uint16)_tstoi(sBuf));
			theApp.mmserver->StopServer();
			theApp.mmserver->Init();
		}
		thePrefs.SetMMIsEnabled(IsDlgButtonChecked(IDC_MMENABLED)!=0);
		if (IsDlgButtonChecked(IDC_MMENABLED))
			theApp.mmserver->Init();
		else
			theApp.mmserver->StopServer();
		GetDlgItem(IDC_MMPASSWORDFIELD)->GetWindowText(sBuf);
		if(sBuf != HIDDEN_PASSWORD)
			thePrefs.SetMMPass(sBuf);

	//MORPH START - UPnP
#ifdef USE_OFFICIAL_UPNP
		if (IsDlgButtonChecked(IDC_WSUPNP))
		{
			ASSERT( thePrefs.IsUPnPEnabled() );
			if (!thePrefs.m_bWebUseUPnP && thePrefs.GetWSIsEnabled() && theApp.m_pUPnPFinder != NULL) // add the port to existing mapping without having šMule restarting (if all conditions are met)
				theApp.m_pUPnPFinder->GetImplementation()->LateEnableWebServerPort(thePrefs.GetWSPort());
			thePrefs.m_bWebUseUPnP = true;
		}
		else
			thePrefs.m_bWebUseUPnP = false;
#else
		if ((UINT)thePrefs.GetUPnPNatWeb() != IsDlgButtonChecked(IDC_WSUPNP))
		{
			theApp.m_UPnP_IGDControlPoint->SetUPnPNat(thePrefs.IsUPnPNat()); // and start/stop nat. 
			thePrefs.SetUPnPNatWeb(IsDlgButtonChecked(IDC_WSUPNP)!=0);
		}
#endif
	//MORPH END   - UPnP

		theApp.emuledlg->serverwnd->UpdateMyInfo();
		SetModified(FALSE);
		SetTmplButtonState();
	}

	return CPropertyPage::OnApply();
}