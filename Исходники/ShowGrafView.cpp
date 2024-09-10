void CShowGrafView::mouseMoveMarkInterval(UINT nFlags, const CPoint &point) {
  if(m_dragging) {
    if(nFlags && MK_LBUTTON) {
      const CRect cr      = getClientRect(this, IDC_SYSTEMPANEL);
      const CRect newRect = CRect(m_mouseDownPoint.x, cr.bottom, point.x, cr.top);
      CClientDC(GetDlgItem(IDC_SYSTEMPANEL)).DrawDragRect(&newRect, CSize(1,1), &m_dragRect, CSize(1,1));
      m_dragRect = newRect;
    } else {
      CClientDC(GetDlgItem(IDC_SYSTEMPANEL)).DrawDragRect(&m_dragRect, CSize(1,1), NULL, CSize(1,1));
      m_dragging = false;
      ClipCursor(NULL);
    }
  }
}