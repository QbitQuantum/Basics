///////////////////////////////////////////////////////////////////////////////
// OnPaint
void CXEdit::OnPaint()
{
	CRect rect;
	GetClientRect(&rect);
	rect.right += 2;

	CDC* pDC = GetDC();
	pDC->FillSolidRect(&rect, ::GetSysColor(COLOR_WINDOW));
	ReleaseDC(pDC);

	CEdit::OnPaint();   // let CEdit draw the text

	//rect.right -= 2;
	rect.left -= 1;
	rect.top -= 1;
	rect.bottom -= 1;

	pDC = GetDC();

	// don't erase the text that CEdit has just drawn
	CBrush* pOldBrush = (CBrush*) pDC->SelectStockObject(NULL_BRUSH);
	CPen pen(PS_SOLID, 1, ::GetSysColor(COLOR_INACTIVECAPTION));   // same as combobox
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->Rectangle(&rect);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	ReleaseDC(pDC);
}