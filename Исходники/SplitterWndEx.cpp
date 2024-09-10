void CSplitterWndEx::OnInvertTracker(const CRect & rect)
{
    ASSERT_VALID(this);
    ASSERT(!rect.IsRectEmpty());
    ASSERT((GetStyle() & WS_CLIPCHILDREN) == 0);
    CDC* pDC = GetDC();
    CBrush* pBrush = CBrush::FromHandle((HBRUSH) GetStockObject(WHITE_BRUSH));
    HBRUSH hOldBrush = NULL;
    if (pBrush != NULL) hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);
    pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATINVERT);
    if (hOldBrush != NULL) SelectObject(pDC->m_hDC, hOldBrush);
    ReleaseDC(pDC);
}