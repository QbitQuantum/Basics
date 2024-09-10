BOOL ExitPropertyPageAdvanced(_In_ HWND hwndDlg, _Inout_ PCOISANE_Data privateData)
{
	SP_DEVINSTALL_PARAMS devInstallParams;
	PWINSANE_Session oSession;
	PWINSANE_Device oDevice;
	LPTSTR lpName;
	LPTSTR lpUsername;
	LPTSTR lpPassword;
	BOOL res;

	lpName = (LPTSTR) HeapAlloc(privateData->hHeap, HEAP_ZERO_MEMORY, sizeof(TCHAR) * MAX_PATH);
	if (lpName) {
		res = GetDlgItemText(hwndDlg, IDC_PROPERTIES_COMBO_SCANNER, lpName, MAX_PATH);
		if (res) {
			if (privateData->lpName) {
				HeapFree(privateData->hHeap, 0, privateData->lpName);
			}
			privateData->lpName = lpName;
		} else {
			HeapFree(privateData->hHeap, 0, lpName);
		}
	} else {
		res = FALSE;
	}

	if (res) {
		lpUsername = (LPTSTR) HeapAlloc(privateData->hHeap, HEAP_ZERO_MEMORY, sizeof(TCHAR) * MAX_PATH);
		if (lpUsername) {
			if (GetDlgItemText(hwndDlg, IDC_PROPERTIES_EDIT_USERNAME, lpUsername, MAX_PATH)) {
				if (privateData->lpUsername) {
					HeapFree(privateData->hHeap, 0, privateData->lpUsername);
				}
				privateData->lpUsername = lpUsername;
			} else {
				HeapFree(privateData->hHeap, 0, lpUsername);
			}
		}

		lpPassword = (LPTSTR) HeapAlloc(privateData->hHeap, HEAP_ZERO_MEMORY, sizeof(TCHAR) * MAX_PATH);
		if (lpPassword) {
			if (GetDlgItemText(hwndDlg, IDC_PROPERTIES_EDIT_PASSWORD, lpPassword, MAX_PATH)) {
				if (privateData->lpPassword) {
					HeapFree(privateData->hHeap, 0, privateData->lpPassword);
				}
				privateData->lpPassword = lpPassword;
			} else {
				HeapFree(privateData->hHeap, 0, lpPassword);
			}
		}

		oSession = WINSANE_Session::Remote(privateData->lpHost, privateData->usPort);
		if (oSession) {
			if (oSession->Init(NULL, NULL) == SANE_STATUS_GOOD) {
				if (oSession->GetDevices() > 0) {
					oDevice = oSession->GetDevice(privateData->lpName);
					if (oDevice) {
						UpdateDeviceInfo(privateData, oDevice);
						UpdateDeviceData(privateData, oDevice);

						ZeroMemory(&devInstallParams, sizeof(SP_DEVINSTALL_PARAMS));
						devInstallParams.cbSize = sizeof(SP_DEVINSTALL_PARAMS);
						res = SetupDiGetDeviceInstallParams(privateData->hDeviceInfoSet, privateData->pDeviceInfoData, &devInstallParams);
						if (res) {
							devInstallParams.FlagsEx |= DI_FLAGSEX_PROPCHANGE_PENDING;
							res = SetupDiSetDeviceInstallParams(privateData->hDeviceInfoSet, privateData->pDeviceInfoData, &devInstallParams);
						}
					} else {
						res = FALSE;
					}
				} else {
					res = FALSE;
				}
				if (oSession->Exit() != SANE_STATUS_GOOD) {
					res = FALSE;
				}
			} else {
				res = FALSE;
			}
			delete oSession;
		} else {
			res = FALSE;
		}
	}

	return res;
}