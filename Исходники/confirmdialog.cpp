static INT_PTR CALLBACK StatusMessageDlgProc(HWND hwndDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static PROTOCOLSETTINGEX* protoSetting = NULL;
	switch(msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);

		protoSetting = (PROTOCOLSETTINGEX *)lParam;
		if (protoSetting->szMsg == NULL) {
			TCHAR* smsg = GetDefaultStatusMessage(protoSetting, GetActualStatus(protoSetting));
			if	(smsg != NULL) {
				SetDlgItemText(hwndDlg, IDC_STSMSG, smsg);
				mir_free(smsg);
			}
		}
		else SetDlgItemTextA(hwndDlg, IDC_STSMSG, protoSetting->szMsg);
		
		{
			TCHAR desc[ 512 ];
			mir_sntprintf(desc, SIZEOF(desc), 
				TranslateT("Set %s message for %s."),
				CallService(MS_CLIST_GETSTATUSMODEDESCRIPTION, GetActualStatus(protoSetting), GSMDF_TCHAR ),
				protoSetting->tszAccName );
			SetDlgItemText(hwndDlg, IDC_DESCRIPTION, desc);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_OK:
			{
				int len = SendMessage(GetDlgItem(hwndDlg, IDC_STSMSG), WM_GETTEXTLENGTH, 0, 0);
				if (len > 0) {
					protoSetting->szMsg = ( char* )realloc(protoSetting->szMsg, len+1);
					if (protoSetting->szMsg != NULL)
						GetDlgItemTextA(hwndDlg, IDC_STSMSG, protoSetting->szMsg, len+1);
				}
				SendMessage(GetParent(hwndDlg), UM_STSMSGDLGCLOSED, (WPARAM)TRUE, 0);
				EndDialog(hwndDlg, IDC_OK);
			}
			break;

		case IDC_CANCEL:
			SendMessage(GetParent(hwndDlg), UM_STSMSGDLGCLOSED, (WPARAM)0, 0);
			EndDialog(hwndDlg, IDC_CANCEL);
			break;
		}
		break;
	}

	return FALSE;
}