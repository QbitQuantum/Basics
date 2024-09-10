LRESULT CSetPgUpdate::OnInitDialog(HWND hDlg, bool abInitial)
{
	ConEmuUpdateSettings* p = &gpSet->UpdSet;

	SetDlgItemText(hDlg, tUpdateVerLocation, p->UpdateVerLocation());

	checkDlgButton(hDlg, cbUpdateCheckOnStartup, p->isUpdateCheckOnStartup);
	checkDlgButton(hDlg, cbUpdateCheckHourly, p->isUpdateCheckHourly);
	checkDlgButton(hDlg, cbUpdateConfirmDownload, !p->isUpdateConfirmDownload);
	checkRadioButton(hDlg, rbUpdateStableOnly, rbUpdateLatestAvailable,
		(p->isUpdateUseBuilds==1) ? rbUpdateStableOnly : (p->isUpdateUseBuilds==3) ? rbUpdatePreview : rbUpdateLatestAvailable);

	checkDlgButton(hDlg, cbUpdateInetTool, p->isUpdateInetTool);
	SetDlgItemText(hDlg, tUpdateInetTool, p->GetUpdateInetToolCmd());

	checkDlgButton(hDlg, cbUpdateUseProxy, p->isUpdateUseProxy);
	SetDlgItemText(hDlg, tUpdateProxy, p->szUpdateProxy);
	SetDlgItemText(hDlg, tUpdateProxyUser, p->szUpdateProxyUser);
	SetDlgItemText(hDlg, tUpdateProxyPassword, p->szUpdateProxyPassword);

	OnButtonClicked(hDlg, NULL, cbUpdateInetTool); // Enable/Disable command field, button '...' and ‘Proxy’ fields

	int nPackage = p->UpdateDownloadSetup(); // 1-exe, 2-7zip
	checkRadioButton(hDlg, rbUpdateUseExe, rbUpdateUseArc, (nPackage==1) ? rbUpdateUseExe : rbUpdateUseArc);
	wchar_t szCPU[4] = L"";
	SetDlgItemText(hDlg, tUpdateExeCmdLine, p->UpdateExeCmdLine(szCPU));
	SetDlgItemText(hDlg, tUpdateArcCmdLine, p->UpdateArcCmdLine());
	SetDlgItemText(hDlg, tUpdatePostUpdateCmd, p->szUpdatePostUpdateCmd);
	enableDlgItem(hDlg, (nPackage==1) ? tUpdateArcCmdLine : tUpdateExeCmdLine, FALSE);
	// Show used or preferred installer bitness
	CEStr szFormat, szTitle; INT_PTR iLen;
	if ((iLen = GetString(hDlg, rbUpdateUseExe, &szFormat.ms_Val)) > 0)
	{
		if (wcsstr(szFormat.ms_Val, L"%s") != NULL)
		{
			wchar_t* psz = szTitle.GetBuffer(iLen+4);
			if (psz)
			{
				_wsprintf(psz, SKIPLEN(iLen+4) szFormat.ms_Val, (nPackage == 1) ? szCPU : WIN3264TEST(L"x86",L"x64"));
				SetDlgItemText(hDlg, rbUpdateUseExe, szTitle);
			}
		}
	}

	checkDlgButton(hDlg, cbUpdateLeavePackages, p->isUpdateLeavePackages);
	SetDlgItemText(hDlg, tUpdateDownloadPath, p->szUpdateDownloadPath);

	return 0;
}