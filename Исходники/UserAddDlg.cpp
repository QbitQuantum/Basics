void CUserAddDlg::OnPaint()
{

	CPaintDC dc(this);
	CDC szMemDC;
	CRect rcClient;
	CRect rc;
	GetClientRect(&rcClient);


	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_HEAD);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	BITMAP bit;
	bitmap.GetBitmap(&bit);
	memdc.SelectObject(&bitmap);
	// rcClient.InflateRect(1,1,1,1);
	dc.StretchBlt(0,0,rcClient.Width(),rcClient.Height(),&memdc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);

	rc = rcClient;
	rc.bottom = 31;
	szMemDC.CreateCompatibleDC(&dc);
	DrawRangeImage(0,&dc,rc);//top

	rc = rcClient;
	rc.right = 1;
	rc.top = rcClient.top - 31;
	DrawRangeImage(1,&dc,rc);//left

	rc = rcClient;
	rc.left = rcClient.right - 5;
	rc.top = rcClient.top - 31;
	DrawRangeImage(1,&dc,rc);//right

	rc = rcClient;
	rc.top = rcClient.bottom - 5;
	DrawRangeImage(0,&dc,rc);//bottom


	COLORREF col = RGB(255,0,255);//修改对话框外形

	CRgn rgn;
	rgn.CreateRoundRectRgn (1, 1, rcClient.Width(), rcClient.Height(),6,6);

	SetWindowRgn (rgn, TRUE);

	dc.SetTextColor(RGB(255,255,240));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(10,5,_T("用户添加"));
}