void CBCGPMSMoneyDemoView::OnDraw(CDC* pDCView)
{
	CBCGPMemDC memDC (*pDCView, this);
	CDC* pDC = &memDC.GetDC ();

	CBCGPMSMoneyDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rectClient;
	GetClientRect (rectClient);

	pDC->FillSolidRect (rectClient, RGB (255, 255, 255));

	pDC->DrawState (m_ptOffset, m_sizeImage, &m_Image, DSS_NORMAL);
}