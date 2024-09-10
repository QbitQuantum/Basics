//The functions below should thread the while loop
static UINT bg1(LPVOID that) {
	while (*lenref == 0) SwitchToThread();//sync (by using another long * as a temp)
	fileDefault = CString(buff);
	if (FileOpen(false)) {
		run((CKODEKDlg *)that, ACTION_DECOMPRESS);
		return 0;
	}
	run((CKODEKDlg *)that, END);
	return -1;
}