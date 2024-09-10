//
// CHistoryPane message handlers
//
void CHistoryPane::OnPaint() 
{
	CPaintDC dc(this);

  CRect r;
  CRgn  rgn;
  CPen  pen;
  uint  w, i;
  uint  y, gap;
  COLORREF colBack;
  
  GetClientRect(&r);
  colBack = GetSysColor(COLOR_3DLIGHT);

  //
  dc.FillSolidRect(0, 0, XBORDER, r.bottom, colBack);
  dc.FillSolidRect(r.right-XBORDER, 0, XBORDER, r.bottom, colBack);

  dc.FillSolidRect(XBORDER, 0, r.right-r.left-2*XBORDER, YBORDER, colBack);
  dc.FillSolidRect(XBORDER, r.bottom-YBORDER, r.right-r.left-2*XBORDER, YBORDER, colBack);

  dc.Draw3dRect(&r, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

  //
  r.DeflateRect(XBORDER, YBORDER);
  rgn.CreateRectRgnIndirect(&r);
  dc.SelectClipRgn(&rgn, RGN_COPY);

  pen.CreatePen(PS_SOLID, 1, RGB(0xff,0x3f,0x00));

  //dc.SetROP2(R2_XORPEN);
  dc.SelectObject(&pen);
  dc.SelectStockObject(NULL_BRUSH);
  dc.SetStretchBltMode(HALFTONE);

  //
  w = m_uWidth;
  y = YBORDER;
  gap = 0;

  for (i=m_uTopItem; i<m_vItems.size(); i++)
  {
    CItem & info = m_vItems[i];
    CRect rTmp(0,0,0,0);

    rTmp = CRect(XBORDER, y, XBORDER+m_uWidth, y+info.h0);
    BitmapBlt(&dc, &rTmp, info.image0, 0);

    if (info.sel0 != rTmp)
    {
      rTmp = info.sel0 + CSize(0,y);
      dc.Rectangle(&rTmp);
    }

    dc.FillSolidRect(XBORDER, y+info.h0, m_uWidth, YSPACE, GetSysColor(COLOR_3DLIGHT));
    //dc.Draw3dRect(XBORDER, y, w, info.h0, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));

    y += info.h0 + YSPACE;
    if (y > r.bottom)
      break;
  }

  if (y < r.bottom)
  {
    gap = r.bottom - y;
    dc.FillSolidRect(XBORDER, y, m_uWidth, r.bottom-y, colBack);
  }

  if (m_bSendScroll ||
      gap != m_uTrailingGap)
  {
    m_uTrailingGap = gap;
    m_bSendScroll = false;
    GetParent()->PostMessage(m_uMsgScroll);
  }
}