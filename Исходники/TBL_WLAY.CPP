/////////////////////////////////////////////////////////////
// The Move Function
/////////////////////////////////////////////////////////////
void ALMAPI TABLE_WLAY::Move(LPRECT newRect)
  {
  if (EqualRect(newRect, &(m_rcItem)) == FALSE)
      {
      OWndInvalidateLogicalRect(m_oiParent, &m_rcItem, TRUE);
      m_rcItem = *newRect;
      table->visRect = *newRect;
      // store the DP rect
      OWndLPtoDP(m_oiParent, (LPPOINT)&table->visRect, 2);

      OWndInvalidateLogicalRect(m_oiParent, &m_rcItem, TRUE);
      }
  }