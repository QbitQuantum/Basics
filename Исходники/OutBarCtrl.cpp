void CNOutBarCtrl::drawAll(CDC *pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CRect rcClient;
	GetClientRect(rcClient);
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());
	CBitmap *oldBitmap = memDC.SelectObject(&bm);

	int obj = HITOBJ(lastHit);
	int index = HITINDEX(lastHit);

	int i;
	for (i = folders.size() - 1; i >= 0; i--)
		drawFolder(&memDC, i, FALSE, (obj == HT_FOLDER && index == i));

	CRect rc;
	getInsideRect(rc);
	drawBackground(&memDC, rc);

	CRgn rgn;
	rgn.CreateRectRgnIndirect(rc);
	memDC.SelectClipRgn(&rgn);

	int max = getMaxVisibleItem();
	for (i = scrollPos(); i <= max; i++)
		drawItem(&memDC, i);

	if (obj == HT_ITEM)
		hilightItem(&memDC, index, FALSE);

	for (i = 1; i >= 0; i--) {
		if (canScroll(i))
			drawScroll(&memDC, i, pressedHit == MAKEHIT(HT_SCROLL, i));
	}

	pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldBitmap);
}