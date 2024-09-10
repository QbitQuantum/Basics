INT_PTR CALLBACK CreateGameDialogWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvt;
	switch(message)
	{
	case WM_CLOSE:
		EndDialog(hDlg, IDCANCEL);
		return (INT_PTR)TRUE;
	case WM_SHOWWINDOW:
		//	Set default port
		SetDlgItemText(hDlg, IDC_PORT, L"1024");
		//	Activate edit to set the text
		SendDlgItemMessage(hDlg, IDC_PORT, WM_ACTIVATE, WA_CLICKACTIVE, 0);
		//	Select text in text box. This should be checked if there exists nicer way to achieve the selection
		SendDlgItemMessage(hDlg, IDC_PORT, WM_LBUTTONDBLCLK, 0, 0);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		{
			wmId = LOWORD(wParam);
			wmEvt= HIWORD(wParam);
			switch(wmId)
			{
			case IDOK:
				{
					Communication::ConnectionSettings connectionSettings;
					LPARAM textLength = SendDlgItemMessageA(hDlg, IDC_PORT, WM_GETTEXTLENGTH, 0, 0);
					char *portText = new char[textLength + 1];
					SendDlgItemMessageA(hDlg, IDC_PORT, WM_GETTEXT, textLength + 1, (LPARAM)portText);
					connectionSettings.port = atoi(portText);
					if(connectionSettings.port <= 0)
						connectionSettings.port = 1024;
					delete[] portText;
					//connectionSettings.port = 
					appState.gameServer().connectionDispatcher()->setConnectionSettings(connectionSettings);
					EndDialog(hDlg, IDOK);
					return (INT_PTR)TRUE;
				}
			case IDCANCEL:
				{
					EndDialog(hDlg, IDCANCEL);
					return (INT_PTR)TRUE;
				}
			}
		}
	}
	return (INT_PTR)FALSE;
}