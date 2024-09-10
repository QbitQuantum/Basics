// 不带缩放的作图
BOOL CbmpPicture::Paint(CDC &dc, const RECT &rcPos)
{
	if (!bmp.GetSafeHandle()) //没加载或加载失败
	{
		return FALSE;
	}
	
	CDC compDc;
	compDc.CreateCompatibleDC(&dc);
	CBitmap *oldBmp = compDc.SelectObject(&bmp);
	dc.SetStretchBltMode(HALFTONE);
	
	if (!dc.BitBlt(rcPos.left, rcPos.top, rcPos.right - rcPos.left, rcPos.bottom - rcPos.top,
		&compDc, 0, 0, SRCCOPY) )
	{
		return FALSE;
	}
	compDc.SelectObject(oldBmp);
	return TRUE;
}