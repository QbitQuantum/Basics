void CDialogThumbs::DrawOwnerDrawCtl( LPDRAWITEMSTRUCT lpDrawItem, HBITMAP hbp )
{
	if (NULL == hbp)
	{
		return;
	}

	SelectObject(dc_memory_, hbp);

	BITMAP bitmap;
	GetObject(hbp, sizeof(bitmap), &bitmap);

	float rate_x = (float)(lpDrawItem->rcItem.right - lpDrawItem->rcItem.left) / bitmap.bmWidth;
	float rate_y = (float)(lpDrawItem->rcItem.bottom - lpDrawItem->rcItem.top) / abs(bitmap.bmHeight);

	RECT rc;
	if (rate_x > rate_y)
	{
		rc.top = lpDrawItem->rcItem.top;
		rc.bottom = lpDrawItem->rcItem.bottom;

		int width = rate_y * bitmap.bmWidth;
		rc.left = 0;
		rc.right = width;
	}
	else
	{
		rc.left = lpDrawItem->rcItem.left;
		rc.right = lpDrawItem->rcItem.right;

		int height = rate_x * abs(bitmap.bmHeight);

		rc.top = 0;
		rc.bottom = height;
	}

	SetStretchBltMode(lpDrawItem->hDC, STRETCH_HALFTONE); 
	StretchBlt(lpDrawItem->hDC, rc.left, rc.top, rc.right, rc.bottom, dc_memory_, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}