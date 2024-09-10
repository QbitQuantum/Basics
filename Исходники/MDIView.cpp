void CMDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
  if(this == GetCapture())
    ReleaseCapture();                                                  // Stop capturing mouse messages

  // Make sure there is an element
  if(m_pTempElement)
  { // Add the element pointer to the sketch
    
    GetDocument()->AddElement(m_pTempElement); 
    InvalidateRect(&m_pTempElement->GetEnclosingRect());
    m_pTempElement.reset();                                            // Reset the element pointer
   }
}