template <class BASE> void CDialogMinTrayBtn<BASE>::MinTrayBtnDraw()
{
	if (!MinTrayBtnIsVisible())
		return;

	CDC	*pDC = GetWindowDC();

	if (pDC == NULL)
		return;

	CRect	rcBtn = MinTrayBtnGetRect();
	UINT	uiState;

	if (IsWindowsClassicStyle())
	{
	//	Button
		uiState = DFCS_BUTTONPUSH;

		if (!m_bMinTrayBtnUp)
			uiState |= DFCS_PUSHED;

		pDC->DrawFrameControl(rcBtn, DFC_BUTTON, uiState);

	//	Dot
		rcBtn.DeflateRect(2,2);

		UINT	iCptWdth = MinTrayBtnGetSize().cy + (CAPTION_BUTTONSPACE << 1);
		UINT	iPixRatio1 = iCptWdth >= 20 ? 2 + ((iCptWdth - 20) >> 3) : (iCptWdth >= 14 ? 2 : 1);
		UINT	iPixRatio2 = iCptWdth >= 12 ? 1 + ((iCptWdth - 12) >> 3) : 0;
		CRect	rcDot(CPoint(0, 0), CPoint((1 + iPixRatio1 * 3) >> 1, iPixRatio1));
		CSize	szSpc((1 + iPixRatio2 * 3) >> 1, iPixRatio2);

		rcDot += rcBtn.BottomRight() - rcDot.Size() - szSpc;

		if (!m_bMinTrayBtnUp)
			rcDot += CPoint(1, 1);

		int	iColor = COLOR_BTNTEXT;

		if (!m_bMinTrayBtnEnabled)
		{
			iColor = COLOR_GRAYTEXT;
			pDC->FillSolidRect(rcDot + CPoint(1, 1), GetSysColor(COLOR_BTNHILIGHT));
		}
		pDC->FillSolidRect(rcDot, GetSysColor(iColor));
	}
	else
	{