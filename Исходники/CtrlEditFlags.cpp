void CCtrlEditFlags::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
  EnableToolTips( TRUE);
  CDC *pDC = GetDC();
  m_rectButton = lpDrawItemStruct->rcItem;
  COLORREF clrrefBcg=GetSysColor(COLOR_MENU);
  pDC->FillSolidRect(&m_rectButton, clrrefBcg);
  m_rectButton.top+=2;
  m_rectButton.bottom-=2;
  m_dx = (m_rectButton.right-m_rectButton.left)/9;

  INDEX ix=0;
  for( INDEX iBit=(m_iCurrentBank+1)*8-1; iBit>=m_iCurrentBank*8; iBit--)
  {
    RECT rectToFill=GetRectForArea(ix);
    ULONG ulBit=(1<<iBit);
    COLORREF clrfColor=CLRF_CLR( C_GRAY);
    // if is editable
    if( m_ulEditable&ulBit)
    {
      // if is not defined
      if(!(m_ulDefined&ulBit))
      {
        clrfColor=CLRF_CLR( C_GRAY);
      }
      else
      {
        // if is checked
        if(m_ulValue&ulBit)
        {
          clrfColor=CLRF_CLR( C_BLACK);
        }
        // it is cleared
        else
        {
          clrfColor=CLRF_CLR( C_WHITE);
        }
      }
      if( !IsWindowEnabled())
      {
        clrfColor=clrrefBcg;
      }
      pDC->FillSolidRect( &rectToFill, clrfColor);
      pDC->DrawEdge( &rectToFill, EDGE_SUNKEN, BF_RECT);
    }
    else
    {
      pDC->DrawEdge( &rectToFill, EDGE_ETCHED, BF_RECT);
    }
    ix++;
  }
  
  if( IsWindowEnabled())
  {
    RECT rectText=GetRectForArea(8);
    CTString strCTBankNo;
    strCTBankNo.PrintF("%d",m_iCurrentBank);
    CString strBankNo=strCTBankNo;
    pDC->SetBkMode( TRANSPARENT);
    pDC->SetTextAlign(TA_CENTER);
    pDC->ExtTextOut( (rectText.left+rectText.right)/2, rectText.top, ETO_CLIPPED, &rectText, strBankNo, 1, NULL);
  }
}