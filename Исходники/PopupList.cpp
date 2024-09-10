// 画图片信息
void CPopupList::DrawWindowEx(CDC &dc, CRect rcClient)
{
	int nItemCount =  m_vecItem.size();
	CRect rcItem;
	CSize sizeImage;
	Graphics graphics(dc);

	for(int i = 0; i < nItemCount; i++)
	{
		EditListItem &editListItem = m_vecItem.at(i);
		rcItem = editListItem.rcItem;
		sizeImage = editListItem.sizeImage;

		// 删除按钮
		if((i == m_nHoverItem) && (m_pImageClose != NULL))
		{
			graphics.DrawImage(m_pImageClose, RectF((Gdiplus::REAL)m_rcClose.left, (Gdiplus::REAL)m_rcClose.top, (Gdiplus::REAL)m_rcClose.Width(), (Gdiplus::REAL)m_rcClose.Height()),
				(Gdiplus::REAL)(m_buttonState * m_sizeClose.cx), 0, (Gdiplus::REAL)m_sizeClose.cx, (Gdiplus::REAL)m_sizeClose.cy, UnitPixel); 
		}

		// 列表图片
		if(editListItem.pImage)
		{	
			CRect rcHead(rcItem.left + 1, rcItem.top + 2, rcItem.left + 1 + rcItem.Height() - 4, rcItem.top + 2 + rcItem.Height() - 4);
			graphics.DrawImage(editListItem.pImage, RectF((Gdiplus::REAL)rcHead.left, (Gdiplus::REAL)rcHead.top, (Gdiplus::REAL)rcHead.Width(), (Gdiplus::REAL)rcHead.Height()),
				0, 0, (Gdiplus::REAL)editListItem.sizeImage.cx, (Gdiplus::REAL)editListItem.sizeImage.cy, UnitPixel);

			DrawImageFrame(graphics, m_pImageHead, rcHead, i == m_nHoverItem ? m_sizeHead.cx : 0, 0, m_sizeHead.cx, m_sizeHead.cy, 5);
		}
	}
}