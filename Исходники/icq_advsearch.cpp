static void searchPackTLVWordLNTS(PBYTE *buf, int *buflen, HWND hwndDlg, UINT idControl, WORD w, WORD wType)
{
	char str[512];

	GetDlgItemTextA(hwndDlg, idControl, str, sizeof(str));

	ppackLETLVWordLNTS(buf, buflen, w, str, wType, 0);
}