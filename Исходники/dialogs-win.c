INT_PTR CALLBACK Pin2DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {	
	static TCHAR *pin2;
	static unsigned int minPin2Length;

	switch(message) {
		case WM_INITDIALOG:			
			HWND previousWindowsHandle;
			HWND pin2EntryWindowHandle;
			HWND parentWindowHandle;

			EstEID_log("[WM_INITDIALOG] begin");
			parentWindowHandle = GetParent(hwnd);
			EstEID_log("parentWindowHandle = %08X, current focus is @ %08X, foregroud window %08X", parentWindowHandle, GetFocus(), GetForegroundWindow());			

			dialogWindowHandle = hwnd;
			EstEID_log("PIN2 dialog window handle = %08X", dialogWindowHandle);
			SetPinDialogLabels(dialogWindowHandle, lParam);				
			SetDialogItemText(dialogWindowHandle, IDC_PIN2_LABEL, l10n("For signing enter PIN2:"));
			SetDialogItemText(dialogWindowHandle, IDOK, l10n("Sign"));
			SetDialogItemText(dialogWindowHandle, IDCANCEL, l10n("Cancel"));
			minPin2Length = ((DialogData *)lParam)->minPin2Length;
			pin2 = ((DialogData *)lParam)->pin2;

			pin2EntryWindowHandle = GetDlgItem(hwnd, IDC_PIN2);
			EstEID_log("PIN2 entry field window handle = %08X", pin2EntryWindowHandle);
			
			previousWindowsHandle = SetFocus(hwnd);
			if (!previousWindowsHandle) {
				EstEID_log("error detected: SetFocus(%08X) returned 0, error code = %li", hwnd, GetLastError());
			}
			else {
				EstEID_log("focus taken from %08X and set to %08X ", previousWindowsHandle, GetFocus());
			}
			EstEID_log("confirming: focus is @ %08X - %s", GetFocus(), GetFocus() == pin2EntryWindowHandle ? "sehr gut!" : "SHOULD NOT BE LIKE THAT!");

			if (GetFocus() != pin2EntryWindowHandle) {
				EstEID_log("second attempt to set focus...");
				previousWindowsHandle = SetFocus(hwnd);
				if (!previousWindowsHandle) {
						EstEID_log("again, error detected: SetFocus(%08X) returned 0, error code = %li", hwnd, GetLastError());
				}
				else {
					EstEID_log("again, focus taken from %08X and set to %08X ", previousWindowsHandle, GetFocus());
				}
				EstEID_log("again, confirming: focus is @ %08X - %s", GetFocus(), GetFocus() == pin2EntryWindowHandle ? "bueno!" : "Firefox? Giving up... Better take Google Chrome.");
			}

			EnableWindow(parentWindowHandle, false); // hack to disable controls in browser window
			
			EstEID_log("[WM_INITDIALOG] end");
			return true;

		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDOK:
					GetDlgItemText(hwnd, IDC_PIN2, pin2, PIN2_MAX_LEN);
				case IDCANCEL:					
					dialogWindowHandle = 0;
					EndDialog(hwnd, LOWORD(wParam));					
					EstEID_log("closing PIN2 dialog, focus is back @ %08X", GetFocus());					
					return true;
			}
			if(HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) == IDC_PIN2) {
				Button_Enable(GetDlgItem(hwnd, IDOK), isAcceptableLengthPIN2(hwnd, IDC_PIN2, minPin2Length));
			}
			return true;
		case WM_CTLCOLORSTATIC:			
			if(GetDlgItem(hwnd, IDC_ERROR) == ((HWND)lParam)){
				return SetMessageLabelColorToRed(wParam);
			}			
		default:
			return false;
	}	
}