void CCustomTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpds)
{
	CDC dc;
	dc.Attach(lpds->hDC);

	DWORD style = GetStyle();

	TCITEM item;	char text[100];
	item.mask = TCIF_IMAGE | TCIF_TEXT;
	item.pszText = text;	item.cchTextMax = 100;
	GetItem(lpds->itemID, &item);
	CConn* con = (CConn*)lpds->itemData;
	COLORREF bkcolor, textcolor;
	dc.SetBkMode(TRANSPARENT);
//設定文字和背景顏色
#ifdef	_COMBO_
	//收到熱訊，或者網頁下載完畢，反白提示!
	if (item.iImage == 5 && !(lpds->itemState & ODS_SELECTED))
#else
	if (item.iImage == 5 && !(lpds->itemState & ODS_SELECTED))	//收到熱訊，反白提示!
#endif

	{
		textcolor = GetSysColor(COLOR_HIGHLIGHTTEXT);
		bkcolor = GetSysColor(COLOR_HIGHLIGHT);
	}
	else
	{
		bkcolor = GetSysColor(COLOR_BTNFACE);

		if (lpds->itemState & ODS_SELECTED)
			textcolor = AppConfig.active_tab_textcolor;
		else
			textcolor = GetSysColor(COLOR_WINDOWTEXT);
	}
//---------------------------------------------------------------

	int icox, icoy;
//	填充背景
	if (style&TCS_BUTTONS)		//是Button形式的
	{
		//	重要，查閱CDC相關文件， CDC::GetHalftoneBrush()
		//	不需要DeleteObject，因為整個程式共用一個brush
		//	此為MFC內部提供，事實上還是建立Bitmap然後CreatePatternBrush
		if (lpds->itemState & ODS_SELECTED)
		{
			CBrush *cbsh = CDC::GetHalftoneBrush();
			//	^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			dc.SetTextColor(GetSysColor(COLOR_3DHILIGHT));
			dc.SetBkColor(GetSysColor(COLOR_BTNFACE));
			FillRect(dc.m_hDC, &lpds->rcItem, (HBRUSH)cbsh->m_hObject);
			OffsetRect(&lpds->rcItem, 2, 2);
		}
		else
			dc.FillSolidRect(&lpds->rcItem, bkcolor);

		InflateRect(&lpds->rcItem, -2, -2);
		icoy = lpds->rcItem.top - 2;
		icox = lpds->rcItem.left + 4;
	}
	else	//Tab 形式
	{
		if (_afxComCtlVersion >= MAKELONG(0, 6))	//Win XP IE 6.0
		{
			icox = lpds->rcItem.left, icoy = lpds->rcItem.top + 2;
			InflateRect(&lpds->rcItem, -1, -2);
			lpds->rcItem.top++;
			if (lpds->itemState & ODS_SELECTED)
			{
				icox += 4;
				lpds->rcItem.left += 2;
				lpds->rcItem.top++;
			}
			dc.FillSolidRect(&lpds->rcItem, bkcolor);
		}
		else	//以下除了xp+ CMCTL32 6.0以外全部適用
		{
			dc.FillSolidRect(&lpds->rcItem, bkcolor);
			InflateRect(&lpds->rcItem, -2, -2);
			if (style & TCS_BOTTOM)
				icoy = lpds->rcItem.top - 2;
			else
			{
				icoy = lpds->rcItem.top;
				lpds->rcItem.top += 2;
			}

			icox = lpds->rcItem.left;
			if (lpds->itemState & ODS_SELECTED)
				icox += 4;
		}
	}
	//畫出 icon
	GetImageList()->Draw(&dc, item.iImage, CPoint(icox, icoy), ILD_TRANSPARENT);

	//輸出文字
	dc.SetTextColor(textcolor);
	lpds->rcItem.left = icox + 16 + 4;
//#if defined(_COMBO_)
//	lpds->rcItem.right-=3;
//#endif
	dc.DrawText(text, strlen(text), &lpds->rcItem, DT_SINGLELINE | DT_END_ELLIPSIS);
	dc.Detach();
}