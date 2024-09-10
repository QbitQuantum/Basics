BOOL StudentDlg::OnEraseBkgnd(CDC * pDC)
{
	CDialogEx::OnEraseBkgnd(pDC);
	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	int bmw, bmh;

	CBitmap C;
	C.LoadBitmapW(IDB_BACKGROUND1);
	dc.SelectObject(&C);
	BITMAP bmap3;
	C.GetBitmap(&bmap3);
	bmw = bmap3.bmWidth; bmh = bmap3.bmHeight;
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0, 0, rect.right, rect.bottom, &dc, 0, 0, bmw, bmh, SRCCOPY);
	DeleteObject(C);

	CBitmap B;
	B.LoadBitmapW(IDB_BAR2);
	dc.SelectObject(&B);
	BITMAP bmap1;
	B.GetBitmap(&bmap1);
	bmw = bmap1.bmWidth; bmh = bmap1.bmHeight;
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0, 0, rect.right, 30, &dc, 0, 0, bmw, bmh, SRCCOPY);
	DeleteObject(B);

	ReleaseDC(&dc);
	return true;
}