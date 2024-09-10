void Protocol::Move
  (
  OpWndItemD* wi,
  LPRECT      lprc
  )

  {
  // make sure the borders are on pixel boundaries
  OWndLPtoDP(m_oiWnd, (LPPOINT)lprc, 2);
  OWndDPtoLP(m_oiWnd, (LPPOINT)lprc, 2);

  if(m_fFrames)
    {
    RECT  rcOld;

    CopyRect(&rcOld, &wi->m_rcItem);
    InvalidateGrabHandles(wi, TRUE);
    wi->Move(lprc);
    InvalidateGrabHandles(wi, FALSE);
    if(OWndIsHwndItem(wi) && !EqualRect(&rcOld, &wi->m_rcItem))
      {
      OWndInvalidateLogicalRect(m_oiWnd, &rcOld, TRUE);
      OWndInvalidateLogicalRect(m_oiWnd, &wi->m_rcItem, TRUE);
      }
    }
  else
    {
    wi->InvalidateGrabHandles(TRUE);
    wi->Move(lprc);
    wi->InvalidateGrabHandles(FALSE);
    }
  }