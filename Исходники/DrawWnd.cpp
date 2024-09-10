void CDrawWnd::draw_bang(int x1, int y1, int x2, int y2)
{
	HDC bgDC1 = CreateCompatibleDC(m_hdc);
	BITMAP temBmp1;
	HBITMAP hStartBmp1 = (HBITMAP) LoadImage(m_hinst,TEXT("res\\map\\爆炸.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	::GetObject(hStartBmp1, sizeof(temBmp1), &temBmp1);
	SelectObject(bgDC1, hStartBmp1);
	TransparentBlt(m_hdc, 40 + 40 * x1 , 40 + 40 * y1 , temBmp1.bmWidth, temBmp1.bmHeight, bgDC1, 0, 0, temBmp1.bmWidth, temBmp1.bmHeight, RGB(255, 255, 255));
	DeleteDC(bgDC1);
	HDC bgDC = CreateCompatibleDC(m_hdc);
	BITMAP temBmp;
	HBITMAP hStartBmp = (HBITMAP) LoadImage(m_hinst, TEXT("res\\map\\爆炸.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	::GetObject(hStartBmp, sizeof(temBmp), &temBmp);
	SelectObject(bgDC, hStartBmp);
	TransparentBlt(m_hdc, 40 + 40 * x2 , 40 + 40 * y2 , temBmp.bmWidth, temBmp.bmHeight, bgDC, 0, 0, temBmp.bmWidth, temBmp.bmHeight, RGB(255, 255, 255));

	DeleteDC(bgDC);
}