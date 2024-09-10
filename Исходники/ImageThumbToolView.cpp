void CImageThumbToolView::OnDraw(CDC* pDC)
{
	CImageThumbToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if (m_index >= 0) {
		if (mode != VIEW) {
			if (m_change) {
				image.Destroy();
				image.Load(pDoc->data.path + "\\" + pDoc->data.thumbs[m_index].image_name);
				pDoc->data.thumbs[m_index].size_x = image.GetWidth();
				pDoc->data.thumbs[m_index].size_y = image.GetHeight();
				m_change = 0;
			}
			/*		CRect rect;
					GetClientRect(rect);
					CDC dcMem;
					CBitmap bmp;
					dcMem.CreateCompatibleDC(pDC);
					bmp.CreateCompatibleBitmap(&dcMem, rect.Width(), rect.Height());
					dcMem.SelectObject(&bmp);
					dcMem.FillSolidRect(rect, pDC->GetBkColor());
					*/
			CRect rect;
			AfxGetMainWnd()->GetWindowRect(&rect);
			AfxGetMainWnd()->MoveWindow(rect.left, rect.top,
				image.GetWidth() + rect.Width() - m_width, image.GetHeight() + rect.Height() - m_height);
			int offset_x, offset_y;
			double scale;
			pDoc->data.getShowOffset(m_index, offset_x, offset_y);
			pDoc->data.getShowScale(m_index, scale);
			offset_x += m_width * 0.5 * (1 - scale);
			offset_y += m_height * 0.5 * (1 - scale);
			int ox = 0, oy = 0, ow = image.GetWidth(), oh = image.GetHeight();
			int tx = offset_x, ty = offset_y, tw = ow * scale, th = oh * scale;
			if (tx < 0) {
				ox -= tx / scale;
				ow += tx / scale;
				tw += tx;
				tx = 0;
			}
			if (ty < 0) {
				oy -= ty / scale;
				oh += ty / scale;
				th += ty;
				ty = 0;
			}
			if (tw > m_width - tx) {
				tw = m_width - tx;
				ow = tw / scale;
			}
			if (th > m_height - ty) {
				th = m_height - ty;
				oh = th / scale;
			}
			::SetStretchBltMode(pDC->m_hDC, HALFTONE);
			::SetBrushOrgEx(pDC->m_hDC, 0, 0, NULL);
			image.StretchBlt(pDC->m_hDC, tx, ty, tw, th,
				ox, oy, ow, oh);
			CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
			pDC->SelectObject(&pen);
			pDC->MoveTo(m_width / 2 - pDoc->data.frame_width / 2, m_height / 2 - pDoc->data.frame_height / 2);
			pDC->LineTo(m_width / 2 - pDoc->data.frame_width / 2, m_height / 2 + pDoc->data.frame_height / 2);
			pDC->LineTo(m_width / 2 + pDoc->data.frame_width / 2, m_height / 2 + pDoc->data.frame_height / 2);
			pDC->LineTo(m_width / 2 + pDoc->data.frame_width / 2, m_height / 2 - pDoc->data.frame_height / 2);
			pDC->LineTo(m_width / 2 - pDoc->data.frame_width / 2, m_height / 2 - pDoc->data.frame_height / 2);
			/*		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, SRCCOPY);
					dcMem.DeleteDC();
					bmp.DeleteObject();
					*/
		}
		else {
			CRect rect;
			AfxGetMainWnd()->GetWindowRect(&rect);
			AfxGetMainWnd()->MoveWindow(rect.left, rect.top,
				900 + rect.Width() - m_width, 675 + rect.Height() - m_height);
			CPoint p = GetScrollPosition();
			int start = p.y / (pDoc->data.frame_height + 15) * 5;
			int end = min(pDoc->data.size(), start + 30);
			for (int i = start; i < end; ++i) {
				CImage image;
				int dy = (i / 5) * (15 + pDoc->data.frame_height) + 7.5;
				int dx = (i % 5) * (20 + pDoc->data.frame_width) + 10;
				image.Load(pDoc->data.path + "\\" + pDoc->data.thumbs[i].image_name);
				pDoc->data.thumbs[i].size_x = image.GetWidth();
				pDoc->data.thumbs[i].size_y = image.GetHeight();
				int offset_x, offset_y;
				double scale;
				pDoc->data.getShowOffset(i, offset_x, offset_y);
				pDoc->data.getShowScale(i, scale);
				offset_x += image.GetWidth() * 0.5 * (1 - scale);
				offset_y += image.GetHeight() * 0.5 * (1 - scale);
				int diff_x = image.GetWidth() / 2 - pDoc->data.frame_width / 2 - offset_x;
				int diff_y = image.GetHeight() / 2 - pDoc->data.frame_height / 2 - offset_y;
				::SetStretchBltMode(pDC->m_hDC, HALFTONE);
				::SetBrushOrgEx(pDC->m_hDC, 0, 0, NULL);
				image.StretchBlt(pDC->m_hDC, dx, dy, pDoc->data.frame_width, pDoc->data.frame_height,
					diff_x / scale, diff_y / scale, pDoc->data.frame_width / scale, pDoc->data.frame_height / scale);
				if (i == m_index) {
					CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
					pDC->SelectObject(&pen);
					pDC->MoveTo((i % 5) * (20 + pDoc->data.frame_width), (i / 5) * (15 + pDoc->data.frame_height));
					pDC->LineTo((i % 5 + 1) * (20 + pDoc->data.frame_width), (i / 5) * (15 + pDoc->data.frame_height));
					pDC->LineTo((i % 5 + 1) * (20 + pDoc->data.frame_width), (i / 5 + 1) * (15 + pDoc->data.frame_height));
					pDC->LineTo((i % 5) * (20 + pDoc->data.frame_width), (i / 5 + 1) * (15 + pDoc->data.frame_height));
					pDC->LineTo((i % 5) * (20 + pDoc->data.frame_width), (i / 5) * (15 + pDoc->data.frame_height));
				}
			}
		}
	}
}