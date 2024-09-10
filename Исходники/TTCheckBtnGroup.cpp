void CTTCheckBtnGroup::OnPaint()
{
	CPaintDC dc(this); 

	CRect clientRect;
	GetClientRect(clientRect);

	if (clientRect.Width() <= 0 || clientRect.Height() <= 0)
		return;

	CMemDC memDC(dc, clientRect);

	CDC* pDC = &memDC.GetDC();

	DrawThemeParentBackground(GetSafeHwnd(), memDC.GetDC().GetSafeHdc(), clientRect);

	Graphics graphics(pDC->GetSafeHdc());
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	graphics.SetTextRenderingHint(TextRenderingHintSingleBitPerPixel);

	// clear background
	CRgn bkgndRgn;
	CRect bkgndRect(clientRect);
	bkgndRect.left += 1;
	bkgndRect.top += 1;
	CreateRectRgnInDevicePoints(pDC, &bkgndRgn, bkgndRect, m_CornerRadius);
	pDC->SelectClipRgn(&bkgndRgn);

	pDC->FillSolidRect(&clientRect, RGB(255, 255, 255));

	CRgn clientRgn;
	CreateRectRgnInDevicePoints(pDC, &clientRgn, clientRect);
	pDC->SelectClipRgn(&clientRgn);

	// Whole border
	Gdiplus::Rect borderRect(clientRect.left, clientRect.top, clientRect.Width(), clientRect.Height());
	borderRect.Inflate(-1, -1);

	if (m_Buttons.size() == 0)
	{
		COLORREF borderColor = m_ColorMap.GetColor(Normal, Border);
		DrawRectArea(borderRect, graphics, borderColor, m_CornerRadius, m_BorderPenWidth);
	}

	for (int btnId = 0; btnId < m_Buttons.size(); ++btnId)
	{
		BtnInfo* pBtnInfo = &m_Buttons[btnId];

		CRgn btnRgn;
		CRect t(pBtnInfo->m_rect);
		t.right += 1; t.bottom += 1;
		CreateRectRgnInDevicePoints(pDC, &btnRgn, t);
		btnRgn.CombineRgn(&btnRgn, &bkgndRgn, RGN_AND);
		pDC->SelectClipRgn(&btnRgn);
		
		ControlState buttonState = GetButtonState(pBtnInfo);

		// Highlight
		if (buttonState != Press)		
			pDC->FillSolidRect(pBtnInfo->m_rect, m_ColorMap.GetColor(buttonState, BorderLight));

		// Border
		graphics.SetClip(btnRgn);
		COLORREF borderColor = m_ColorMap.GetColor(buttonState, Border);
		DrawRectArea(borderRect, graphics, borderColor, m_CornerRadius, m_BorderPenWidth);
		graphics.ResetClip();

		CRgn offsetRgn1;
		offsetRgn1.CreateRectRgn(0, 0, 0, 0);
		offsetRgn1.CopyRgn(&btnRgn);
		offsetRgn1.OffsetRgn(m_BorderPenWidth + 1, m_BorderPenWidth + 1);

		CRgn offsetRgn2;
		offsetRgn2.CreateRectRgn(0, 0, 0, 0);
		offsetRgn2.CopyRgn(&btnRgn);
		offsetRgn2.OffsetRgn(-(m_BorderPenWidth + 1), -(m_BorderPenWidth + 1));

		CRgn backRgn;
		backRgn.CreateRectRgn(0, 0, 0, 0);
		backRgn.CombineRgn(&offsetRgn1, &offsetRgn2, RGN_AND);
		pDC->SelectClipRgn(&backRgn);

		if (buttonState != Mouseover)
		{
			DrawGradient(pDC, t);
			/*Draw4ColorsGradientRect(t, *pDC,
				m_ColorMap.GetColor(buttonState, BackgroundTopGradientStart),
				m_ColorMap.GetColor(buttonState, BackgroundTopGradientFinish),
				m_ColorMap.GetColor(buttonState, BackgroundBottomGradientStart),
				m_ColorMap.GetColor(buttonState, BackgroundBottomGradientFinish),
				m_CornerRadius, TRUE);*/
		}

		COLORREF textColor = RGB(80,80,80);//COLOR_GRAYTEXT;//COLOR_BTNTEXT;
		/*if (buttonState == Press)
			textColor = RGB(0, 122, 224);*/

		pDC->SelectClipRgn(&btnRgn);
		CFont* pFont = GetFont();
		
		int nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
		CTTButton::DrawCaptionText(pDC, &pBtnInfo->m_rect, &pBtnInfo->m_rect, pBtnInfo->m_text, nFormat, pFont, textColor);
	}

	pDC->SelectClipRgn(&clientRgn);
	for (int btnId = 1; btnId < m_Buttons.size(); ++btnId)
	{
		BtnInfo* pPrevBtnInfo = &m_Buttons[btnId - 1];
		BtnInfo* pCurBtnInfo = &m_Buttons[btnId];

		ControlState prevBtnState = GetButtonState(pPrevBtnInfo);
		ControlState curBtnState = GetButtonState(pCurBtnInfo);

		ControlState state = Normal;
		if (prevBtnState == Press || curBtnState == Press)
			state = Press;
		else if (prevBtnState == Mouseover || curBtnState == Mouseover)
			state = Mouseover;

		COLORREF borderColor = m_ColorMap.GetColor(state, Border);

		CPen borderPen(PS_SOLID, m_BorderPenWidth, borderColor);
		pDC->SelectObject(borderPen);

		pDC->MoveTo(pPrevBtnInfo->m_rect.right, pPrevBtnInfo->m_rect.top);
		pDC->LineTo(pPrevBtnInfo->m_rect.right, pPrevBtnInfo->m_rect.bottom);
	}
}