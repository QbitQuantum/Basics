void CImconView::DrawSelectionRect(LPRECT lpRect)
{
  if (IsRectEmpty (lpRect))
    return;

  // Open DC
  CDC *pDC = GetDC();
  pDC->SetViewportOrg(-m_ptScrollOffset);

  // Draw rectangular clip region
  pDC->PatBlt(lpRect->left, lpRect->top,
              lpRect->right - lpRect->left, 1,
              DSTINVERT);
  pDC->PatBlt(lpRect->left, lpRect->bottom,
              1, -(lpRect->bottom - lpRect->top),
              DSTINVERT);
  pDC->PatBlt(lpRect->right - 1, lpRect->top,
              1, lpRect->bottom - lpRect->top,
              DSTINVERT);
  pDC->PatBlt(lpRect->right, lpRect->bottom - 1,
              -(lpRect->right - lpRect->left), 1,
              DSTINVERT);

  ReleaseDC(pDC);
}