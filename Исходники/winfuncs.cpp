void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBitmap)
{
	HBITMAP hOldbm;
	HDC hMemDC;
	BITMAP bm;
	POINT ptSize, ptOrg;

	hMemDC = CreateCompatibleDC(hdc);
	hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);
	if (hOldbm)
	{
		SetMapMode(hMemDC, GetMapMode(hdc));
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
		ptSize.x = bm.bmWidth;
		ptSize.y = bm.bmHeight;

		DPtoLP(hdc, &ptSize, 1);

		ptOrg.x = 0;
		ptOrg.y = 0;

		DPtoLP(hMemDC, &ptOrg, 1);

		BitBlt(hdc, x, y, ptSize.x, ptSize.y, hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

		SelectObject(hMemDC, hOldbm);
	}

	DeleteDC(hMemDC);
}