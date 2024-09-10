/*
*--------------------------------------------------------------------------------
*  函数名:	BeginDraw
*  功能	 :	用当前画刷颜色填充封闭区域
*  参数	 :	CPoint ptPoint	 -   当前的坐标点
*  算法  :	重载函数，调用 API 函数进行填充
*--------------------------------------------------------------------------------
*/
void CPaintTub::BeginDraw(const CPoint& ptPoint)
{
	HDC hDC = m_hDC;

	// 得到当前坐标点的颜色
	COLORREF crCurPos = GetPixel(hDC, ptPoint.x, ptPoint.y);

	HBRUSH hBrush = CreateSolidBrush(m_crPenColor);
	HBRUSH hOldBrush = (HBRUSH) SelectObject(hDC, hBrush);

	// 填充颜色, Windows API
	ExtFloodFill(hDC, ptPoint.x, ptPoint.y, crCurPos, FLOODFILLSURFACE);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
	DeleteObject(hBrush);
}