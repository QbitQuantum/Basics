void CCircuitView::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	// ¸Þ¸ð¸® DC ¼±¾ð
	CDC memDC;
	CBitmap *pOldBitmap, bitmap;

	// È­¸é DC¿Í È£È¯µÇ´Â ¸Þ¸ð¸® DC °´Ã¼¸¦ »ý¼º
	memDC.CreateCompatibleDC(pDC);

	// ¸¶Âù°¡Áö·Î È­¸é DC¿Í È£È¯µÇ´Â Bitmap »ý¼º
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS); // Èò»öÀ¸·Î ÃÊ±âÈ­

	DrawImage(&memDC);			// ¸Þ¸ð¸® DC¿¡ ±×¸®±â

	// ¸Þ¸ð¸® DC¸¦ È­¸é DC¿¡ °í¼Ó º¹»ç
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}