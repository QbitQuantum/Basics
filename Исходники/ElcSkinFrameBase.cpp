void CElcSkinFrameBase::DrawCaptionMin(CDC* pDC, HICON hIcon)
{
	CRect rect;
	int nImageIndex = m_bActivated ? 0 : 1;

	// draw background
	thePainter.DrawImageGDI(pDC->GetSafeHdc(), 
		&m_skin.caption_min, 
		m_rect, 
		nImageIndex, 
		0, 
		0, 
		0);

	// draw icon
	m_bHasIcon = FALSE;
	rect.left = FRAME_ICON_MARGIN + FRAME_ICON_MARGIN;
	rect.right = m_rect.right - FRAME_ICON_MARGIN - FRAME_ICON_MARGIN;;
	if (hIcon) {
		m_bHasIcon = TRUE;
		::DrawIconEx(pDC->GetSafeHdc(), 
			rect.left, 
			(m_rect.Height() - FRAME_ICON_SIZE) / 2, 
			hIcon, 
			FRAME_ICON_SIZE, 
			FRAME_ICON_SIZE, 
			0, 
			NULL, 
			DI_NORMAL);

		rect.left += FRAME_ICON_SIZE + FRAME_ICON_MARGIN;
	}

	// draw buttons
	for (size_t i = 0; i < m_arrButton.size(); i ++)
	{
		if (m_arrButton[i].type >= ESNWT_CUSTOM_BASE )
			continue;

		nImageIndex = 0;
		if (m_nLBDownItem != ESNWT_NONE && m_nLBDownItem == m_arrButton[i].type) {
			nImageIndex = 2;
		}
		else if (m_nActiveButton == (int)i) {
				nImageIndex = 1;
		}

		if (!m_arrButton[i].bEnable || !m_bActivated)
			nImageIndex = 3;

		if (m_arrButton[i].type == ESNWT_MINIMIZE) {
			if (::IsIconic(m_hDerive))
				nImageIndex += 4;
		}

		CRect rcBtn = CalcPos(m_arrButton[i].pButton);
		int nYPos = (m_rect.Height() - rcBtn.Height()) / 2 - rcBtn.top;
		rcBtn.OffsetRect(0, nYPos);
		thePainter.DrawImageGDI(
			pDC->GetSafeHdc(), 
			&m_arrButton[i].pButton->image, 
			rcBtn, 
			nImageIndex,
			0,
			0,
			0);

		if (rect.right > rcBtn.left - FRAME_ICON_MARGIN)
			rect.right = rcBtn.left - FRAME_ICON_MARGIN;
	}

	// draw text
	TCHAR szText[256] = {0};
	::GetWindowText(m_hDerive, szText, 256);
	CFont * pOldFont = pDC->SelectObject(&m_ftCaption);
	pDC->SetTextColor(m_skin.crCaption);
	rect.top = 0;
	rect.bottom = m_rect.Height();
	pDC->DrawText(szText, rect, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX|DT_WORD_ELLIPSIS);
	pDC->SelectObject(pOldFont);
}