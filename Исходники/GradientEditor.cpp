void CGradientEditor::CStepHandle::OnDraw(HDC hDC, const LPRECT clientRect)
{
	int xSrc = dragging ? WIDTH : 0;
	UpdateBounds();
	MaskBlt(hDC, bounds.left, bounds.top, WIDTH, HEIGHT, parent->shBitmapDC, xSrc, 0, parent->shBmpMask, xSrc, 0, MAKEROP4(SRCCOPY, 0xAA0029));
	SetBrushOrgEx(hDC, -20, 0, NULL);
	SelectObject(hDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hDC, gradient->GetStepColor(stepID));
	WorkingMaskBlt(hDC, bounds.left, bounds.top, WIDTH, HEIGHT, hDC, xSrc, 0, parent->shBmpColorMask, xSrc, 0, MAKEROP4(PATCOPY, 0xAA0029));
}