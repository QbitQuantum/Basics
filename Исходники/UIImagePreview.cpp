void CUIImagePreview::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	CMemDC memDC(dc, this);
	CDC* pDC = &memDC.GetDC();

	CRect rectClient;
	CRgn rgnClip;
	this->GetClientRect(&rectClient);
	rgnClip.CreateRectRgnIndirect(&rectClient);
	pDC->SelectClipRgn(&rgnClip);
	pDC->FillRect(&rectClient, &afxGlobalData.brBtnFace);
	if(!m_imgPreview.IsNull())
		m_imgPreview.BitBlt(pDC->GetSafeHdc(), 0, 0);
}