void CSimplePanelDlg::DrawBk()
{
	CDC* pDC = GetDC();

	CRect rc;
	GetClientRect(&rc);

	int nHeight = m_pImLineBK->GetHeight();
	int nWidth = m_pImLineBK->GetWidth();

	CEsayMemDC* pmemDC = new CEsayMemDC(*pDC, rc);
	Gdiplus::Color cl = Gdiplus::Color::White;
	Gdiplus::SolidBrush brush(cl);

	Gdiplus::Graphics gr(pmemDC->GetDC());
	gr.FillRectangle(&brush, rc.left, rc.top, rc.Width(), rc.Height());

	//顶部文字
	Gdiplus::SolidBrush brushBkWord(Gdiplus::Color(149,158,168));
	std::wstring str = L"第一辆车";

	Gdiplus::PointF pointFBkWord(60+nWidth, 0);
	Gdiplus::RectF rectBkWord(pointFBkWord, Gdiplus::SizeF(145, 46));
	Gdiplus::Font fontBkWord(L"方正兰亭黑简体", 24 , Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::StringFormat stringFormatBkWord;
	stringFormatBkWord.SetAlignment(Gdiplus::StringAlignmentFar);
	stringFormatBkWord.SetLineAlignment(Gdiplus::StringAlignmentCenter);

	gr.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	gr.DrawString(str.c_str(), str.size(), &fontBkWord, rectBkWord, &stringFormatBkWord, &brushBkWord);

	str = L"第二辆车";

	pointFBkWord.X = 60 + nWidth + 145;
	rectBkWord.X = pointFBkWord.X;
	gr.DrawString(str.c_str(), str.size(), &fontBkWord, rectBkWord, &stringFormatBkWord, &brushBkWord);

	str = L"第一辆车";

	pointFBkWord.X = 60 + nWidth*2 + 145 * 2+ 100 + 10;
	rectBkWord.X = pointFBkWord.X;
	gr.DrawString(str.c_str(), str.size(), &fontBkWord, rectBkWord, &stringFormatBkWord, &brushBkWord);

	str = L"第二辆车";

	pointFBkWord.X = 60 + nWidth * 2 + 145 * 3+ 100 + 10;
	rectBkWord.X = pointFBkWord.X;
	gr.DrawString(str.c_str(), str.size(), &fontBkWord, rectBkWord, &stringFormatBkWord, &brushBkWord);

	//底部分割线
	Gdiplus::SolidBrush brushLine(Gdiplus::Color(215, 215, 215));
	Gdiplus::Pen penLine(&brushLine, 1);

	gr.DrawLine(&penLine, Gdiplus::Point(rc.left, rc.bottom-1), Gdiplus::Point(rc.right, rc.bottom-1));

	//中间竖线
	Gdiplus::SolidBrush brushLineM(Gdiplus::Color(215, 215, 215));
	Gdiplus::Pen penLineM(&brushLineM, 2);

	gr.DrawLine(&penLineM, Gdiplus::Point(541, rc.top + 46), Gdiplus::Point(541, rc.top + nHeight*3 + 64));
	pmemDC->BltMem(*pDC);

	delete pmemDC;

	ReleaseDC(pDC);
}