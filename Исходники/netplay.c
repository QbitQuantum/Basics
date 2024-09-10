static void FixCDis(HWND hParent, int how) {
	int x;

	for (x = 200; x <= 206; x++)
		EnableWindow(GetDlgItem(hParent, x), how);
}