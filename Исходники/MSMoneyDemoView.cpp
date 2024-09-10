void CMSMoneyDemoView::OnDraw(CDC* pDCView)
{
	CMemDC memDC (*pDCView, this);
	CDC* pDC = &memDC.GetDC ();

	CRect rectClient;
	GetClientRect (rectClient);

	pDC->FillSolidRect (rectClient, RGB (255, 255, 255));

	pDC->DrawState (CPoint (20, 20), m_sizeImage, &m_Image, DSS_NORMAL);
}