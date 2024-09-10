/*
 * @implemented
 */
DWORD WINAPI drvCommConfigDialogW(LPCWSTR lpszDevice,
	HWND hWnd,
	LPCOMMCONFIG lpCommConfig)
{
	DIALOG_INFO DialogInfo;

	if(!lpszDevice || !lpCommConfig)
	{
		return ERROR_INVALID_PARAMETER;
	}

	DialogInfo.lpszDevice = lpszDevice;
	DialogInfo.lpCC = lpCommConfig;

	return DialogBoxParamW(hDllInstance, MAKEINTRESOURCEW(IDD_COMMDLG),
					hWnd, (DLGPROC)CommDlgProc, (LPARAM)&DialogInfo);
}