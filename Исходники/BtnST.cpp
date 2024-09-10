void CButtonST::OnMouseMove(UINT nFlags, CPoint point)
{
  CWnd* pWnd;  // Finestra attiva
  CWnd* pParent; // Finestra che contiene il bottone

  CButton::OnMouseMove(nFlags, point);

  // If the mouse enter the button with the left button pressed
  // then do nothing
  if (nFlags & MK_LBUTTON && m_MouseOnButton == FALSE) return;

  // If our button is not flat then do nothing
  if (m_bIsFlat == FALSE) return;

  pWnd = GetActiveWindow();
  pParent = GetOwner();

	if ((GetCapture() != this) && 
		(
#ifndef ST_LIKEIE
		pWnd != NULL && 
#endif
		pParent != NULL)) 
	{
		m_MouseOnButton = TRUE;
		//SetFocus();	// Thanks Ralph!
		SetCapture();
		Invalidate();
	}
	else
  {
	CRect rc;
	GetClientRect(&rc);
	if (!rc.PtInRect(point))
	{
	  // Redraw only if mouse goes out
	  if (m_MouseOnButton == TRUE)
	  {
		m_MouseOnButton = FALSE;
		Invalidate();
	  }
	  // If user is NOT pressing left button then release capture!
	  if (!(nFlags & MK_LBUTTON)) ReleaseCapture();
	}
  }
} // End of OnMouseMove