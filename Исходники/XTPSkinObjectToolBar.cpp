void CXTPSkinObjectToolBar::DrawButton(CDC* pDC, int nIndex)
{
	CToolBarCtrl* pToolBar = (CToolBarCtrl*)this;

	TBBUTTON tbb;
	pToolBar->GetButton(nIndex, &tbb);

	CRect rc;
	if (!pToolBar->GetItemRect(nIndex, rc))
		return;

	int dxText = rc.Width() - (2 * GetMetrics()->m_cxEdge);
	int dyText = rc.Height() - (2 * GetMetrics()->m_cyEdge);

	NMTBCUSTOMDRAW tbcd;
	ZeroMemory(&tbcd, sizeof(NMTBCUSTOMDRAW));
	tbcd.nmcd.hdc = pDC->GetSafeHdc();
	tbcd.nmcd.rc = rc;
	tbcd.nmcd.dwItemSpec = tbb.idCommand;
	tbcd.nmcd.lItemlParam = tbb.dwData;

	SetRect(&tbcd.rcText, 0, 0, dxText, dyText);

	int nHot = (int)pToolBar->SendMessage(TB_GETHOTITEM);
	BOOL fHotTrack = nHot == nIndex;
	BOOL bPressed = tbb.fsState & TBSTATE_PRESSED;
	BOOL bChecked = tbb.fsState & TBSTATE_CHECKED;
	BOOL bEnabled = tbb.fsState & TBSTATE_ENABLED;

	tbcd.nmcd.uItemState = (fHotTrack ? CDIS_HOT : 0)
		| (bPressed ? CDIS_SELECTED : 0)
		| (bChecked ? CDIS_CHECKED : 0)
		| (bEnabled ? 0 : CDIS_DISABLED);

	LRESULT dwCustom = CustomDrawNotify(CDDS_ITEMPREPAINT, &tbcd.nmcd);

	fHotTrack = tbcd.nmcd.uItemState & CDIS_HOT;
	bPressed = tbcd.nmcd.uItemState & CDIS_SELECTED;
	bChecked = tbcd.nmcd.uItemState & CDIS_CHECKED;
	bEnabled = (tbcd.nmcd.uItemState & CDIS_DISABLED) == 0;

	if (!(dwCustom & CDRF_SKIPDEFAULT))
	{
		int dxFace = rc.Width() - 2 * GetMetrics()->m_cxEdge;

		dxText = tbcd.rcText.right - tbcd.rcText.left;
		dyText = tbcd.rcText.bottom - tbcd.rcText.top;

		int x = rc.left + GetMetrics()->m_cxEdge;
		int y = rc.top + GetMetrics()->m_cyEdge;

		BOOL bSplit = HasSplitDropDown(&tbb);
		int cxMenuCheck = bSplit ? GetSystemMetrics(SM_CYMENUCHECK) : 0;

		if (HasDropDownArrow(&tbb))
		{
			dxFace -= 5;
			dxText -= bSplit ? cxMenuCheck : 5;
		}


		LRESULT lPad = SendMessage(TB_GETPADDING);
		int yPad = HIWORD(lPad);
		int xPad = LOWORD(lPad);

		int yOffset = (yPad - (2 * GetMetrics()->m_cyEdge)) / 2;
		if (yOffset < 0)
			yOffset = 0;

		HIMAGELIST himl = GetImageList(HIML_NORMAL, 0);

		int iDxBitmap = 16, iDyBitmap = 16;

		if (himl)
		{
			ImageList_GetIconSize(himl, &iDxBitmap, &iDyBitmap);
		}

		int xCenterOffset =  (dxFace - iDxBitmap) / 2;

		if (GetStyle() & TBSTYLE_LIST)
		{
			xCenterOffset = xPad / 2;
		}
		else if (bSplit)
		{
			xCenterOffset = (dxFace + GetMetrics()->m_cxEdge * 2 - (iDxBitmap + cxMenuCheck)) / 2;
		}

		if ((bPressed || bChecked) && (!(dwCustom & TBCDRF_NOOFFSET)))
		{
			xCenterOffset++;
			yOffset++;
		}

		CXTPSkinManagerClass* pClass = GetSkinClass();

		if (!(dwCustom & TBCDRF_NOEDGES))
		{
			if (bSplit)
			{

				CRect rcSplit(rc), rcSplitDropDown(rc);
				rcSplit.right -= cxMenuCheck;
				rcSplitDropDown.left = rcSplit.right;

				pClass->DrawThemeBackground(pDC, TP_SPLITBUTTON, !bEnabled ? TS_DISABLED :
					bPressed ? TS_PRESSED : bChecked ? TS_CHECKED : fHotTrack ? TS_HOT : TS_NORMAL, &rcSplit);
				pClass->DrawThemeBackground(pDC, TP_SPLITBUTTONDROPDOWN, !bEnabled ? TS_DISABLED :
					bPressed ? TS_PRESSED : bChecked ? TS_CHECKED : fHotTrack ? TS_HOT : TS_NORMAL, &rcSplitDropDown);
			}
			else
			{
				pClass->DrawThemeBackground(pDC, TP_BUTTON, !bEnabled ? TS_DISABLED :
					bPressed ? TS_PRESSED : bChecked ? TS_CHECKED : fHotTrack ? TS_HOT : TS_NORMAL, &rc);
			}
		}

		BOOL fImage = HasButtonImage(&tbb);

		if (fImage)
		{
			int yImage = y, xImage = x;

			if (GetStyle() & TBSTYLE_LIST)
			{
				if (iDyBitmap + yPad >= rc.Height())
					yImage -= GetMetrics()->m_cyEdge;

				if (iDxBitmap + xPad >= rc.Width())
					xImage -= GetMetrics()->m_cxEdge;
			}

			DrawButtonImage(pDC, xImage + xCenterOffset, yImage + yOffset, nIndex);
		}


		CString strText;

		SendMessage(TB_GETBUTTONTEXT, tbb.idCommand, (LPARAM)(LPTSTR)strText.GetBuffer(256));
		strText.ReleaseBuffer();

	#ifdef _UNICODE
		if (strText.IsEmpty() && (int)SendMessage(WM_NOTIFYFORMAT, 0, NF_QUERY) == NFR_ANSI)
		{
			char tText[256];
			tText[0] = 0;
			SendMessage(TB_GETBUTTONTEXTA, tbb.idCommand, (LPARAM)tText);
			strText = tText;
		}
	#endif

		if (!strText.IsEmpty())
		{
			if ((bPressed || bChecked) && (!(dwCustom & TBCDRF_NOOFFSET)))
			{
				x++;
				if (GetStyle() & TBSTYLE_LIST)
					y++;
			}


			if (GetStyle() & TBSTYLE_LIST)
			{
				int iListGap = (GetMetrics()->m_cxEdge * 2);

				if (fImage)
				{
					x += iDxBitmap + iListGap;
					dxText -= iDxBitmap + iListGap;
				}
			}
			else
			{
				y += yOffset + iDyBitmap;
				dyText -= yOffset + iDyBitmap;
			}

			DWORD uiStyle = DT_END_ELLIPSIS;

			int nTextRows = (int)SendMessage(TB_GETTEXTROWS);

			if (nTextRows > 1)
				uiStyle |= DT_WORDBREAK | DT_EDITCONTROL;
			else
				uiStyle |= DT_SINGLELINE;

			if (GetStyle() & TBSTYLE_LIST)
			{
				uiStyle |= DT_LEFT | DT_VCENTER | DT_SINGLELINE;
			}
			else
			{
				uiStyle |= DT_CENTER;
			}

			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(bEnabled ? GetColor(COLOR_BTNTEXT) :
				GetColor(COLOR_BTNSHADOW));

			if (dxText > 0)
			{
				CRect rcText(x + 1, y + 1, x + 1 + dxText, y + 1 + dyText);
				pDC->DrawText(strText, rcText, uiStyle);
			}
		}


		if (!bSplit && HasDropDownArrow(&tbb))
		{
			CPoint pt(rc.right - 6, rc.CenterPoint().y);
			if (bPressed)
				pt.Offset(1, 1);

			CXTPDrawHelpers::Triangle(pDC, CPoint(pt.x - 2, pt.y - 1), CPoint(pt.x + 2, pt.y - 1), CPoint(pt.x, pt.y + 1), GetColor(COLOR_BTNTEXT));
		}
	}

	if (dwCustom & CDRF_NOTIFYPOSTPAINT)
		CustomDrawNotify(CDDS_ITEMPOSTPAINT, &tbcd.nmcd);
}