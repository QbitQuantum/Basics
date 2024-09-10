void CFrameHolder::PaintFrame2k(HWND hWnd, HDC hdc, RECT &cr)
{
	//RECT cr;
	//GetWindowRect(hWnd, &cr);
	//OffsetRect(&cr, -cr.left, -cr.top);

	//TODO: Обработка XP
	HPEN hOldPen = (HPEN)SelectObject(hdc, (HPEN)GetStockObject(BLACK_PEN));
	HBRUSH hOldBr = (HBRUSH)SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));

	HPEN hPenHilight = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
	HPEN hPenLight = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DLIGHT));
	HPEN hPenShadow = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
	HPEN hPenDkShadow = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW));
	HPEN hPenFace = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));
	//TODO: разобраться с шириной рамки, активной/неактивной
	HPEN hPenBorder = CreatePen(PS_SOLID, 1, GetSysColor(mb_NcActive ? COLOR_ACTIVEBORDER : COLOR_INACTIVEBORDER));
	//TODO: градиент
	HBRUSH hBrCaption = GetSysColorBrush(mb_NcActive ? COLOR_ACTIVECAPTION : COLOR_INACTIVECAPTION);
	//
	int nCaptionY = GetSystemMetrics(SM_CYCAPTION);

	SelectObject(hdc, hPenLight);
	MoveToEx(hdc, cr.left, cr.bottom-1, NULL); LineTo(hdc, cr.left, 0); LineTo(hdc, cr.right-1, 0);
	SelectObject(hdc, hPenHilight);
	MoveToEx(hdc, cr.left+1, cr.bottom-2, NULL); LineTo(hdc, cr.left+1, 1); LineTo(hdc, cr.right-2, 1);
	SelectObject(hdc, hPenDkShadow);
	MoveToEx(hdc, cr.left, cr.bottom-1, NULL); LineTo(hdc, cr.right-1, cr.bottom-1); LineTo(hdc, cr.right-1, -1);
	SelectObject(hdc, hPenShadow);
	MoveToEx(hdc, cr.left+1, cr.bottom-2, NULL); LineTo(hdc, cr.right-2, cr.bottom-2); LineTo(hdc, cr.right-2, 0);
	// рамка. обычно это 1 пиксел цвета кнопки
	SelectObject(hdc, hPenBorder); //TODO: но может быть и более одного пиксела
	Rectangle(hdc, cr.left+2, cr.top+2, cr.right-2, cr.bottom-2);

	//TODO: Заливка заголовка через GradientFill
	SelectObject(hdc, hPenFace); SelectObject(hdc, hBrCaption);
	Rectangle(hdc, cr.left+3, cr.top+3, cr.right-3, cr.top+nCaptionY+4);
	//что осталось
	SelectObject(hdc, hPenFace);
	//Rectangle(hdc, cr.left+3, cr.top+3+nCaptionY, cr.right-3, cr.bottom-3);
	MoveToEx(hdc, cr.left+3, cr.top+3+nCaptionY, 0);
	LineTo(hdc, cr.left+3, cr.bottom-3);
	LineTo(hdc, cr.right-3, cr.bottom-3);
	LineTo(hdc, cr.right-3, cr.top+3+nCaptionY);


	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBr);

	DeleteObject(hPenHilight); DeleteObject(hPenLight); DeleteObject(hPenShadow); DeleteObject(hPenDkShadow);
	DeleteObject(hPenFace); DeleteObject(hPenBorder);

	cr.left += 4; cr.right -= 4; cr.bottom -= 4; cr.top += 4+nCaptionY;
}