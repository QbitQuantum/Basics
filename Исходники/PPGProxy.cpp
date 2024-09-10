BOOL CPPgProxy::OnApply()
{
	USES_CONVERSION;
	thePrefs.SetProxyASCWOP(IsDlgButtonChecked(IDC_ASCWOP));
	proxy.UseProxy=(IsDlgButtonChecked(IDC_ENABLEPROXY));
	proxy.EnablePassword = ((CButton*)GetDlgItem(IDC_ENABLEAUTH))->GetCheck();
	proxy.type = ((CComboBox*)GetDlgItem(IDC_PROXYTYPE))->GetCurSel();

	if(GetDlgItem(IDC_PROXYNAME)->GetWindowTextLength())
	{ 
		GetDlgItem(IDC_PROXYNAME)->GetWindowText(proxy.name, ARRSIZE(proxy.name));
	}
	else
	{
		proxy.name[0] = _T('\0');
        proxy.UseProxy = false;
	}

	if(GetDlgItem(IDC_PROXYPORT)->GetWindowTextLength())
	{ 
		TCHAR buffer[6];
		GetDlgItem(IDC_PROXYPORT)->GetWindowText(buffer,ARRSIZE(buffer));
		proxy.port = (_tstoi(buffer)) ? _tstoi(buffer) : 1080;
	}
	else
		proxy.port = 1080;

	if(GetDlgItem(IDC_USERNAME_A)->GetWindowTextLength())
	{ 
		CString strUser;
		GetDlgItem(IDC_USERNAME_A)->GetWindowText(strUser);
		_snprintf(proxy.user, ARRSIZE(proxy.user), "%s", T2CA(strUser));
	}
	else
	{
		proxy.user[0] = '\0';
		proxy.EnablePassword = false;
	}

	if(GetDlgItem(IDC_PASSWORD)->GetWindowTextLength())
	{ 
		CString strPasswd;
		GetDlgItem(IDC_PASSWORD)->GetWindowText(strPasswd);
		_snprintf(proxy.password, ARRSIZE(proxy.password), "%s", T2CA(strPasswd));
	}
	else
	{
		proxy.password[0] = '\0';
		proxy.EnablePassword = false;
	}
	thePrefs.SetProxySettings(proxy);
	LoadSettings();
	return TRUE;
}