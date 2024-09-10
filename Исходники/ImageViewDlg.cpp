// 画图片
void CImageViewDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (nIDCtl == m_imageStatic.GetDlgCtrlID())
	{
		CImage buffer;
		buffer.Create(lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top, 32);
		HDC dc = buffer.GetDC();
		SetStretchBltMode(dc, HALFTONE);

		FillRect(dc, &lpDrawItemStruct->rcItem, (HBRUSH)GetStockObject(WHITE_BRUSH));
		CRect rect;
		m_imageStatic.GetWindowRect(rect);
		int yOffset = -m_imageScrollBar.GetScrollPos();
		for (const CImage& i : m_image)
		{
			if (i.IsNull())
				continue;
			SIZE size = GetImageSize(i);
			if (yOffset >= rect.Height())
				break;
			if (yOffset + size.cy > 0)
				i.Draw(dc, 0, yOffset, size.cx, size.cy);

			yOffset += size.cy;
		}
		FrameRect(dc, &lpDrawItemStruct->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));

		buffer.ReleaseDC();
		buffer.Draw(lpDrawItemStruct->hDC, 0, 0);
		return;
	}

	CModelessDlg::OnDrawItem(nIDCtl, lpDrawItemStruct);
}