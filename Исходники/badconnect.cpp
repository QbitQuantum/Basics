INT_PTR CALLBACK DlgProcYAMNBadConnection(HWND hDlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITDIALOG:
		{
			BOOL ShowPopup,ShowMsg,ShowIco;
			HACCOUNT ActualAccount;
			DWORD  ErrorCode;
			char* TitleStrA;
			char *Message1A=NULL;
			TCHAR *Message1W=NULL;
			POPUPDATAT BadConnectPopup;

			ActualAccount=((struct BadConnectionParam *)lParam)->account;
			ErrorCode=((struct BadConnectionParam *)lParam)->errcode;
#ifdef DEBUG_SYNCHRO
			DebugLog(SynchroFile,"BadConnect:ActualAccountSO-read wait\n");
#endif
			if (WAIT_OBJECT_0 != WaitToReadFcn(ActualAccount->AccountAccessSO))
			{
#ifdef DEBUG_SYNCHRO
				DebugLog(SynchroFile,"BadConnect:ActualAccountSO-read wait failed\n");
#endif
				return FALSE;
			}
#ifdef DEBUG_SYNCHRO
			DebugLog(SynchroFile,"BadConnect:ActualAccountSO-read enter\n");
#endif
			int size = (int)(strlen(ActualAccount->Name)+strlen(Translate(BADCONNECTTITLE)));
			TitleStrA = new char[size];
			mir_snprintf(TitleStrA, size, Translate(BADCONNECTTITLE), ActualAccount->Name);

			ShowPopup=ActualAccount->BadConnectN.Flags & YAMN_ACC_POP;
			ShowMsg=ActualAccount->BadConnectN.Flags & YAMN_ACC_MSG;
			ShowIco=ActualAccount->BadConnectN.Flags & YAMN_ACC_ICO;

			if (ShowPopup) {
				BadConnectPopup.lchIcon = g_LoadIconEx(3);
				BadConnectPopup.colorBack = ActualAccount->BadConnectN.Flags & YAMN_ACC_POPC ? ActualAccount->BadConnectN.PopupB : GetSysColor(COLOR_BTNFACE);
				BadConnectPopup.colorText = ActualAccount->BadConnectN.Flags & YAMN_ACC_POPC ? ActualAccount->BadConnectN.PopupT : GetSysColor(COLOR_WINDOWTEXT);
				BadConnectPopup.iSeconds = ActualAccount->BadConnectN.PopupTime;

				BadConnectPopup.PluginWindowProc = BadConnectPopupProc;
				BadConnectPopup.PluginData = ActualAccount;
				lstrcpyn(BadConnectPopup.lptzContactName, _A2T(ActualAccount->Name), SIZEOF(BadConnectPopup.lptzContactName));
			}

			if (ActualAccount->Plugin->Fcn != NULL && ActualAccount->Plugin->Fcn->GetErrorStringWFcnPtr != NULL) {
				Message1W = ActualAccount->Plugin->Fcn->GetErrorStringWFcnPtr(ErrorCode);
				SetDlgItemText(hDlg,IDC_STATICMSG,Message1W);
				lstrcpyn(BadConnectPopup.lptzText,Message1W,sizeof(BadConnectPopup.lptzText));
				if (ShowPopup)
					PUAddPopupT(&BadConnectPopup);
			}
			else if (ActualAccount->Plugin->Fcn != NULL && ActualAccount->Plugin->Fcn->GetErrorStringAFcnPtr != NULL)
			{
				Message1W=ActualAccount->Plugin->Fcn->GetErrorStringWFcnPtr(ErrorCode);
				SetDlgItemText(hDlg,IDC_STATICMSG,Message1W);
				lstrcpyn(BadConnectPopup.lptzText,Message1W,sizeof(BadConnectPopup.lptzText));
				if (ShowPopup)
					PUAddPopupT(&BadConnectPopup);
			}
			else
			{
				Message1W=TranslateT("Unknown error");
				SetDlgItemText(hDlg,IDC_STATICMSG,Message1W);
				lstrcpyn(BadConnectPopup.lptzText,Message1W,sizeof(BadConnectPopup.lptzText));
				if (ShowPopup)
					PUAddPopupT(&BadConnectPopup);
			}

			if (!ShowMsg && !ShowIco)
				DestroyWindow(hDlg);
#ifdef DEBUG_SYNCHRO
			DebugLog(SynchroFile,"BadConnect:ActualAccountSO-read done\n");
#endif
			ReadDoneFcn(ActualAccount->AccountAccessSO);

			SetWindowTextA(hDlg, TitleStrA);
			delete[] TitleStrA;
			if (Message1A != NULL)
				delete[] Message1A;
			if (ActualAccount->Plugin->Fcn != NULL && ActualAccount->Plugin->Fcn->DeleteErrorStringFcnPtr != NULL && Message1A != NULL)
				ActualAccount->Plugin->Fcn->DeleteErrorStringFcnPtr(Message1A);
			if (ActualAccount->Plugin->Fcn != NULL && ActualAccount->Plugin->Fcn->DeleteErrorStringFcnPtr != NULL && Message1W != NULL)
				ActualAccount->Plugin->Fcn->DeleteErrorStringFcnPtr(Message1W);
			return 0;
		}
		case WM_DESTROY:
		{
			NOTIFYICONDATA nid;

			ZeroMemory(&nid,sizeof(NOTIFYICONDATA));
			nid.cbSize=sizeof(NOTIFYICONDATA);
			nid.hWnd=hDlg;
			nid.uID=0;
			Shell_NotifyIcon(NIM_DELETE,&nid);
			PostQuitMessage(0);
			break;
		}
		case WM_YAMN_NOTIFYICON:
			switch (lParam)
			{
				case WM_LBUTTONDBLCLK:
				          ShowWindow(hDlg,SW_SHOWNORMAL);
				          SetForegroundWindow(hDlg);
				          break;
			}
			return 0;
		case WM_CHAR:
			switch((TCHAR)wParam)
			{
				case 27:
				case 13:
					DestroyWindow(hDlg);
					break;
			}
			break;
		case WM_SYSCOMMAND:
			switch(wParam)
			{
				case SC_CLOSE:
					DestroyWindow(hDlg);
					break;
			}
		case WM_COMMAND:
		{
			WORD wNotifyCode = HIWORD(wParam);
			switch(LOWORD(wParam))
			{
				case IDC_BTNOK:
					DestroyWindow(hDlg);
					break;
			}
			break;
		}
	}
	return 0;
}