void CMonitorWidget::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rc;
   GetWindowRect(rc);
   ClientToScreen(&point);

   int cx = m_ptStartDrag.x - point.x;
   int cy = m_ptStartDrag.y - point.y;

   int nLeft = rc.left - cx;
   int nTop = rc.top - cy;
   int nRight = rc.right - cx;
   int nBottom = rc.bottom - cy;

   if(m_bLimitToWindow && m_bDisableLimitToWindow == false)
   {
      CRect rcWnd;
      CWnd *pParentRef = GetParent();
      if ( pParentRef != NULL )
      {
         pParentRef->GetWindowRect(rcWnd);

         if(rcWnd.left > nLeft)
            nLeft = rcWnd.left;
         if (rcWnd.top > nTop)
            nTop = rcWnd.top;
         if (rcWnd.right < nRight)
            nLeft = rcWnd.right - rc.Width();
         if (rcWnd.bottom < nBottom)
            nTop = rcWnd.bottom - rc.Height();
      }
   }

   if(nLeft != rc.left || nTop != rc.top)
   {
      if(m_bLeftButtonPressed && m_bEnableDrag)
      {
         SetWindowPos(NULL, nLeft, nTop, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
         m_ptStartDrag = point;
         SavePosition();
      }
   }
   CWnd::OnMouseMove(nFlags, point);
}