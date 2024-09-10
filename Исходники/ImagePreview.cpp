void CImagePreview::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	CMemDC memDC(dc, this);
	CDC* pDC = &memDC.GetDC();

	CRect rcClient;
	this->GetClientRect(&rcClient);
	CBrush* pOldBrush=pDC->SelectObject(&afxGlobalData.brBlack);
	pDC->Rectangle(&rcClient);
	pOldBrush=pDC->SelectObject((CBrush*)pDC->SelectStockObject(NULL_BRUSH));
	CRect rcBorder=m_rcImage;
	rcBorder.DeflateRect(-1,-1);
	pDC->Rectangle(rcBorder);
	pDC->SelectObject(pOldBrush);

	if(!m_strProperty.IsEmpty())
		CRenderEngine::DrawImageString(pDC->GetSafeHdc(),m_pManager,m_rcImage,rcClient,	m_strProperty,NULL);
}