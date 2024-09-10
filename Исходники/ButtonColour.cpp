void CColourButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC*	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect	rc = lpDrawItemStruct->rcItem;

	if (lpDrawItemStruct->CtlType == ODT_BUTTON)
	{
		// Draw 3D frame
   if (lpDrawItemStruct->itemState & (ODS_SELECTED | ODS_DISABLED))
  		pDC->DrawEdge(rc, EDGE_SUNKEN, BF_RECT|BF_ADJUST);
   else
  		pDC->DrawEdge(rc, EDGE_RAISED, BF_RECT|BF_ADJUST);

		// Draw colour
		pDC->FillSolidRect(rc, m_colour);


  // if it has the focus, draw a dotted line
  if (lpDrawItemStruct->itemState  & ODS_FOCUS)
    {
    CRect rcFocus (rc);
    rcFocus.DeflateRect (1, 1);
     if (lpDrawItemStruct->itemState & ODS_SELECTED)
       rcFocus.OffsetRect (-1, -1);  // move text as button moves
    pDC->DrawFocusRect (rcFocus); 
    }

    // Draw button text
   CString strText;
   GetWindowText(strText);

   COLORREF crOldColor;

   // if colour is dark, use white, otherwise use black
   if (((GetRValue (m_colour) & 0xFF) +
       (GetGValue (m_colour) & 0xFF) +
       (GetBValue (m_colour) & 0xFF) ) < (128 * 3))
     crOldColor = pDC->SetTextColor(RGB(255,255,255));
   else
     crOldColor = pDC->SetTextColor(RGB(0,0,0));
   if (lpDrawItemStruct->itemState & ODS_SELECTED)
     rc.OffsetRect (-1, -1);  // move text as button moves
   pDC->DrawText (strText, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
   pDC->SetTextColor(crOldColor);


	}
}