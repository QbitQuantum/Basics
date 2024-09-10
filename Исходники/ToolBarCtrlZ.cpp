void CToolBarCtrlZ::DrawItem(CDC *pDC, int iIndex, const CRect &rtItem, BOOL bHover)
{
	UINT			uItemId;
	UINT			uItemState;
	TBBUTTON		tbb;


	TCHAR			szText[1024];
	TBBUTTONINFO	tbi;
	CArray<CxImage*, CxImage*>	*parrImgs = NULL;
	CxImage			*pIconImg = NULL;		
	int				iIconTop;
	CRect			rtDraw;
	CRect			rtText;
	COLORREF		clrText;
	
	CClientRect		rtClient(this);
	rtDraw = rtItem;
	rtDraw.top = rtClient.top;
	rtDraw.bottom = rtClient.bottom;

	if (!GetButton(iIndex, &tbb))
		return;

	uItemId = tbb.idCommand;
	uItemState = GetState(uItemId);

	parrImgs = &m_arrImgs;
	if ( !IsButtonEnabled(uItemId) )
	{
		clrText = RGB(204, 128, 128);
		if (0 != m_arrDisableImgs.GetCount())
			parrImgs = &m_arrDisableImgs;
	}
	else
	{
		clrText = RGB(255, 254, 253);

		if (TBSTATE_PRESSED & uItemState/*IsButtonPressed(uItemId)*/)
			rtDraw.OffsetRect(1, 1);
		else if (bHover/*iIndex == GetHotItem()*/)
			rtDraw.OffsetRect(-1, -2);
	}


	ZeroMemory(&tbi, sizeof(TBBUTTONINFO));
	tbi.cbSize = sizeof(TBBUTTONINFO);
	tbi.dwMask = TBIF_TEXT | TBIF_IMAGE;
	tbi.pszText = szText;
	tbi.cchText = 1024;
	//if (GetButtonInfo(p->nmcd.dwItemSpec, &tbi))
	GetButtonInfo(uItemId, &tbi);
	{

		rtText = rtDraw;

		if (tbi.iImage < parrImgs->GetCount())
		{
			pIconImg = parrImgs->GetAt(tbi.iImage);
			if (NULL != pIconImg)
			{
				iIconTop = rtDraw.Height() - pIconImg->GetHeight();
				iIconTop /= 2;
				iIconTop += rtDraw.top;
				pIconImg->Draw(pDC->GetSafeHdc(), rtDraw.left, iIconTop);
				rtText.left += pIconImg->GetWidth() + 4;
			}
		}


		{
			CWndFontDC	fontDC(pDC->GetSafeHdc(), GetSafeHwnd());
			CTextDC		textDC(pDC->GetSafeHdc(), clrText);
			
			pDC->DrawText(tbi.pszText, -1, &rtText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
	}

}