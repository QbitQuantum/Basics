int CColoredButton::OnToolHitTest( CPoint point, TOOLINFO* pTI ) const
{
  UBYTE ubR, ubG, ubB;
  UBYTE ubH, ubS, ubV, ubA;
  ubH = m_ubComponents[0][0];
  ubS = m_ubComponents[0][1];
  ubV = m_ubComponents[0][2];
  ubA = m_ubComponents[0][3];
  ubR = m_ubComponents[1][0];
  ubG = m_ubComponents[1][1];
  ubB = m_ubComponents[1][2];
  
  CTString strColor;
  if( m_bMixedColor)
  {
    strColor.PrintF( "Mixed color");
  }
  else
  {
    strColor.PrintF( "HSV=(%d,%d,%d),   RGB=(%d,%d,%d),    Alpha=%d", ubH, ubS, ubV, ubR, ubG, ubB, ubA);
  }
  pTI->lpszText = (char *)malloc( strlen(strColor)+1);
  strcpy( pTI->lpszText, strColor);
  RECT rectToolTip;
  rectToolTip.left = 50;
  rectToolTip.right = 60;
  rectToolTip.top = 50;
  rectToolTip.bottom = 60;
  pTI->hwnd = GetParent()->m_hWnd;
  pTI->uId = (UINT) m_hWnd;
  pTI->rect = rectToolTip;
  pTI->uFlags = TTF_IDISHWND;
  return 1;
}