static BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	HWND 			hwndChild;
	TCHAR			szFormat[64],
					szBuffer[64];


#ifndef WIN32
	hwndChild = GetFirstChild(hwnd);
	while (hwndChild)
	{
		SetWindowFont(hwndChild, hFontDialog, FALSE);
		hwndChild = GetNextSibling(hwndChild);
	}
#endif
  	
	LoadString(hInstance, IDS_MIO_TITLE, szFormat, SIZEOF_IN_CHAR(szFormat));
	wsprintf(szBuffer, szFormat, wMIOSlotNumber);
	SetWindowText(hwnd, szBuffer);

	if (hwndChild = GetDlgItem(hwnd, IDC_MIO_TYPE))
	{
		SetWindowWord(hwndChild, GWW_TRAYLEVEL, 1000);
		SetWindowText(hwndChild, mio_card[wMIOSlotNumber - 1].mioType);
	}

	if (hwndChild = GetDlgItem(hwnd, IDC_MIO_DESCRIPTION))
	{
		SetWindowWord(hwndChild, GWW_TRAYLEVEL, 1000);
		SetWindowText(hwndChild, mio_card[wMIOSlotNumber - 1].mioInfo);
	}

	return TRUE;
}