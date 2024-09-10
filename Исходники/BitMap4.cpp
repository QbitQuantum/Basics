//-----------------------------------------------------------
void DrawStone( HDC hdc, int x, int y, char stone)
{
	HDC memDC		= CreateCompatibleDC(hdc);
	HBITMAP old;
	if( stone == BLACK)	
		old = (HBITMAP)SelectObject(memDC, hBlack);
	else
		old = (HBITMAP)SelectObject(memDC, hWhite);
//	BitBlt(hdc, x, y, 29, 29, memDC, 0, 0, SRCCOPY);
	TransparentBlt(hdc, x, y, 29, 29, memDC, 0, 0, 29, 29, RGB(255, 0, 0));
	SelectObject(memDC, old);

	DeleteDC(memDC);
}