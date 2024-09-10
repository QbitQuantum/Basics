void CButtonCx::DrawString(CDC *drawDC, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// テキストを得る。
	CString title;
	GetWindowText(title);

	// テキストが空の場合および GDI+ Font/Brush が設定されていない場合何もしない。
	if (title.IsEmpty() || m_GpFont == NULL || m_GpBrush == NULL)
	{
		return;
	}

	// 透過モードにする。
	drawDC->SetBkMode(TRANSPARENT);

	// テキストの描画位置
	CRect rect = (CRect) (lpDrawItemStruct->rcItem); // クライアント四角形の取得
	// マージン設定
	rect.top += m_Margin.top;
	rect.left += m_Margin.left;
	rect.bottom -= m_Margin.bottom;
	rect.right -= m_Margin.right;

	CArray<CString, CString> arr;
	arr.RemoveAll();

	CString resToken;
	int curPos = 0;
	resToken = title.Tokenize(L"\r\n", curPos);
	while (resToken != L"")
	{
		arr.Add(resToken);
		resToken = title.Tokenize(L"\r\n", curPos);
	}

	if (m_FontType == FT_GDI_PLUS || m_FontType == FT_AUTO)	// GDI+
	{
		Gdiplus::Graphics g(drawDC->m_hDC);

		const Gdiplus::PointF pointF(0.0, 0.0);
		Gdiplus::RectF extentF;

		for (int i = 0; i < arr.GetCount(); i++)
		{
			CRect r;
			r.top = (LONG) (((double) rect.Height()) / arr.GetCount() * i);
			r.bottom = (LONG) (((double) rect.Height()) / arr.GetCount() * (i + 1));
			r.left = rect.left;
			r.right = rect.right;

			g.MeasureString(arr.GetAt(i), arr.GetAt(i).GetLength() + 1, m_GpFont, pointF, &extentF); // "+ 1" for workdaround 

			REAL y;
			FontFamily ff;
			m_GpFont->GetFamily(&ff);
			REAL ascent = (REAL) ff.GetCellAscent(FontStyleRegular);
			REAL lineSpacing = (REAL) ff.GetLineSpacing(FontStyleRegular);

			y = r.CenterPoint().y - (extentF.Height * ascent / lineSpacing) / 2;

			Gdiplus::PointF pt(rect.CenterPoint().x - (extentF.Width / 2), y);
			Gdiplus::RectF rectF(pt.X, pt.Y, (REAL) extentF.Width, (REAL) extentF.Height);

			g.SetTextRenderingHint(TextRenderingHintAntiAlias);
			g.DrawString(arr.GetAt(i), -1, m_GpFont, rectF, m_GpStringformat, m_GpBrush);
		}
	}
	else // GDI
	{
		for (int i = 0; i < arr.GetCount(); i++)
		{
			CRect r;
			r.top = rect.top + (LONG) (((double) rect.Height()) / arr.GetCount() * i);
			r.bottom = rect.top + (LONG) (((double) rect.Height()) / arr.GetCount() * (i + 1));
			r.left = rect.left;
			r.right = rect.right;

			CRect rectI;
			CSize extent;
			HGDIOBJ oldFont = drawDC->SelectObject(m_Font);
			GetTextExtentPoint32(drawDC->m_hDC, arr.GetAt(i), arr.GetAt(i).GetLength() + 1, &extent);
			rectI.top = r.top + (r.Height() - extent.cy) / 2;
			rectI.bottom = rectI.top + extent.cy;
			rectI.left = r.left;
			rectI.right = r.right;
			DrawText(drawDC->m_hDC, arr.GetAt(i), arr.GetAt(i).GetLength(), r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			drawDC->SelectObject(oldFont);
		}
	}
	// いつか DirectWrite 描画に対応したいものである。。。
}