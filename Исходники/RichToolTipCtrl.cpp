void CRichToolTipCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
  LPNMTTCUSTOMDRAW lpttcd = (LPNMTTCUSTOMDRAW)pNMHDR;
  *pResult = CDRF_DODEFAULT;

  if (! ::IsWindow(m_edit.m_hWnd))
    return; // can't do it!

  switch (lpttcd->nmcd.dwDrawStage)
  {
  case CDDS_PREPAINT:
    *pResult = CDRF_NOTIFYPOSTPAINT;	// we want post-paint notifications
    break;

  case CDDS_POSTPAINT:
    {
      // paint the whole window with the system tool-tip background colour
      CRect rcWindow(lpttcd->nmcd.rc);
      SendMessage(TTM_ADJUSTRECT, TRUE, (LPARAM)&rcWindow); // need to get the tip's window rect
      CDC* pDC = CDC::FromHandle(lpttcd->nmcd.hdc);

      // if we're using themes, paint the background with the theme's tooltip background
      BOOL bPainted = FALSE;
      if (s_xpStyle.IsAppXPStyled())
      {
	HTHEME hTheme = s_xpStyle.OpenThemeData(NULL, L"TOOLTIP");
	if (hTheme != NULL)
	{
	  if (s_xpStyle.IsThemeBackgroundPartiallyTransparent(hTheme, TTP_STANDARD, TTSS_NORMAL))
	    s_xpStyle.DrawThemeParentBackground(m_hWnd, lpttcd->nmcd.hdc, &rcWindow);
	  bPainted = (s_xpStyle.DrawThemeBackground(hTheme, lpttcd->nmcd.hdc, TTP_STANDARD, TTSS_NORMAL, &rcWindow) == S_OK);
	}
      }
      if (! bPainted) // not painted using theme, so paint with tool-tip colour
	pDC->FillSolidRect(&rcWindow, GetTipBkColor());

      // FormatRange needs its rect in twips
      // a twip is 1/20 of a printer's point (1,440 twips equal one inch)
      int nLogPixelsX = ::GetDeviceCaps(lpttcd->nmcd.hdc, LOGPIXELSX);
      int nLogPixelsY = ::GetDeviceCaps(lpttcd->nmcd.hdc, LOGPIXELSY);

      // get the drawing rect, and convert to twips
      CRect rc(lpttcd->nmcd.rc);
      rc.DeflateRect(1, 1, 1, 1); // give it a small margin
      rc.left = MulDiv(rc.left, 1440, nLogPixelsX);
      rc.right = MulDiv(rc.right, 1440, nLogPixelsX);
      rc.top = MulDiv(rc.top, 1440, nLogPixelsY);
      rc.bottom = MulDiv(rc.bottom, 1440, nLogPixelsY);

      // use the rich edit control to draw to our device context
      FORMATRANGE fr;
      fr.hdc = lpttcd->nmcd.hdc;
      fr.hdcTarget = lpttcd->nmcd.hdc;
      fr.chrg.cpMin = 0;
      fr.chrg.cpMax = -1;
      fr.rc = rc; // in twips
      fr.rcPage = fr.rc;
      m_edit.FormatRange(&fr, TRUE);
      m_edit.DisplayBand(&rc);
      m_edit.FormatRange(NULL, FALSE);	// get the control to free its cached info

      *pResult = CDRF_SKIPDEFAULT;  // we don't want the default drawing
    }
    break;
  }
}