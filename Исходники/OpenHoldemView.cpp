void COpenHoldemView::DrawBalanceBox(const int chair) {
	CPen		*pTempPen = NULL, oldpen;
	CBrush	*pTempBrush = NULL, oldbrush;
	RECT		textrect = {0}, drawrect = {0};
	CFont		*oldfont = NULL, cFont;
	CString	t = "";
	int			left = 0, top = 0, right = 0, bottom = 0;
	CDC			*pDC = GetDC();
	static RECT	balance_rect_last[10] = {0};
  // Background color
	pDC->SetBkColor(COLOR_GRAY);
  // Figure placement of box
	left = _client_rect.right * pc[p_tablemap->nchairs()][chair][0] - 26;
	top = _client_rect.bottom * pc[p_tablemap->nchairs()][chair][1] + 30;
	right = _client_rect.right * pc[p_tablemap->nchairs()][chair][0] + 25;
	bottom = _client_rect.bottom * pc[p_tablemap->nchairs()][chair][1] + 45;
  // Set font basics
	_logfont.lfHeight = -12;
	_logfont.lfWeight = FW_NORMAL;
	cFont.CreateFontIndirect(&_logfont);
	oldfont = pDC->SelectObject(&cFont);
	pDC->SetTextColor(COLOR_BLACK);
  if (p_scraper_access->IsPlayerSeated(chair) 
		  || p_scraper_access->IsPlayerActive(chair)) 	{
    pTempPen = (CPen*)pDC->SelectObject(&_black_pen);
		oldpen.FromHandle((HPEN)pTempPen);					// Save old pen
		pTempBrush = (CBrush*)pDC->SelectObject(&_white_brush);
		oldbrush.FromHandle((HBRUSH)pTempBrush);			// Save old brush

		// Format Text
		if (p_table_state->_players[chair]._active) 	{
			t = Number2CString(p_table_state->_players[chair]._balance);
		}	else {
			t.Format("Out (%s)", Number2CString(p_table_state->_players[chair]._balance));
		}
	}	else {
		pTempPen = (CPen*)pDC->SelectObject(&_white_dot_pen);
		oldpen.FromHandle((HPEN)pTempPen);					// Save old pen
		pTempBrush = (CBrush*)pDC->SelectObject(&_gray_brush);
		oldbrush.FromHandle((HBRUSH)pTempBrush);			// Save old brush
    t = "";
	}
  // Calc rectangle size for text
	textrect.left = 0;
	textrect.top = 0;
	textrect.right = 0;
	textrect.bottom = 0;
	pDC->DrawText(t.GetString(), t.GetLength(), &textrect, DT_CALCRECT);
  // Figure out placement of rectangle
	drawrect.left = left < (left+(right-left)/2)-textrect.right/2-3 ? left : (left+(right-left)/2)-textrect.right/2-3;
	drawrect.top = top;
	drawrect.right = right > (left+(right-left)/2)+textrect.right/2+3 ? right : (left+(right-left)/2)+textrect.right/2+3;
	drawrect.bottom = bottom;
  // Invalidate everything if the balance has decreased in width
	if (balance_rect_last[chair].right - balance_rect_last[chair].left != drawrect.right - drawrect.left) {
		InvalidateRect(NULL, true);
	}
  // Draw it
	pDC->SetBkMode(OPAQUE);
	pDC->Rectangle(drawrect.left, drawrect.top, drawrect.right, drawrect.bottom);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(t.GetString(), t.GetLength(), &drawrect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	balance_rect_last[chair].left = drawrect.left;
	balance_rect_last[chair].top = drawrect.top;
	balance_rect_last[chair].right = drawrect.right;
	balance_rect_last[chair].bottom = drawrect.bottom;

	// Restore original pen and brush
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldfont);
	cFont.DeleteObject();
	ReleaseDC(pDC);
}