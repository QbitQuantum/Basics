//////オイルパワーの描画////////////
int OIL::Paint_Oil(HDC hdc)
{
	HDC hdc_work;
	hdc_work = CreateCompatibleDC(hdc);

	SelectObject(hdc_work, hb_OilGageback);
	TransparentBlt(hdc, 10, 11, 320, 50, hdc_work, 0, 0, 320, 50, RGB(0, 0, 255));

	SelectObject(hdc_work, hb_OilPower);
	BitBlt(hdc, 10, 20, Power_w, 35, hdc_work, 0, 0, SRCCOPY);

	DeleteDC(hdc_work);
	return 0;
}