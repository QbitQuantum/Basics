int CTabCtrl2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rc;
	GetWindowRect(rc);
	CDC* dc = GetDC();

	HDC hDCMem = CreateCompatibleDC(dc->GetSafeHdc());
	HBITMAP hBmp = CreateCompatibleBitmap(dc->GetSafeHdc(), rc.right - rc.left, rc.bottom - rc.top);
	HGDIOBJ hBmpOld = SelectObject(hDCMem, hBmp);

	SendMessage(WM_PRINTCLIENT, (WPARAM)hDCMem, (LPARAM)(PRF_ERASEBKGND | PRF_CLIENT | PRF_NONCLIENT));

	hBgBrush = CreatePatternBrush(hBmp);

	SelectObject(hDCMem, hBmpOld);

	DeleteObject(hBmp);
	DeleteDC(hDCMem);
	ReleaseDC(dc);	

	return 0;
}