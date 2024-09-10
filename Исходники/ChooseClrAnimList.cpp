void CChooseClrAnimList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC *pDC;

	pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	//dc.Attach(lpDrawItemStruct->hDC);

	CRect rcDraw = lpDrawItemStruct->rcItem;

	if (lpDrawItemStruct->itemID >= 0)
	{
		if (lpDrawItemStruct->itemAction & ODA_SELECT)
		{
			CBrush brRect;
			if (lpDrawItemStruct->itemState & ODS_SELECTED)
			{
				// Draw selection
				brRect.CreateSolidBrush( RGB(0, 0, 128));
			}
			else
			{
				brRect.CreateSolidBrush( RGB(255, 255, 255) );
			}

			pDC->FillRect( rcDraw, &brRect );
		}
		
		CString sTxt;
		GetText(lpDrawItemStruct->itemID, sTxt);

		CK_FAVOURITE *pFavourite = (CK_FAVOURITE *)GetItemData(lpDrawItemStruct->itemID);

		CSize szText = pDC->GetTextExtent( sTxt );

		pDC->TextOut(rcDraw.left + 2, rcDraw.top + (rcDraw.Height() / 2) - (szText.cy / 2), sTxt);

		// Draw the keyframes

		CRect rcFrame;
		rcFrame.left   = rcDraw.left + szText.cx + 10;
		rcFrame.top	   = rcDraw.top + 2;
		rcFrame.right  = rcDraw.right;
		rcFrame.bottom = rcDraw.bottom - 2;

		CBrush brBlack(RGB(0, 0, 0));
		pDC->FrameRect(&rcFrame, &brBlack);

		// Fill in the frame with the colour keys

		rcFrame.left ++;
		rcFrame.top ++;
		rcFrame.bottom --;
		rcFrame.right --;

		m_posColRatio = 1.0f / rcFrame.Width();

		for (int i = 0; i < rcFrame.Width(); i ++)
		{
			int r, g, b;

			PosToCol(pFavourite, i, &r, &g, &b);
				
			CBrush brCol(RGB(r, g, b));
			pDC->FillRect(CRect(i + rcFrame.left, rcFrame.top, rcFrame.left + i + 1, rcFrame.Height() + rcFrame.top), &brCol);
		}
	}
}