void CComboColorPicker::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	CBrush brushBlack;
	brushBlack.CreateStockObject(BLACK_BRUSH);
	
	if (!dc.Attach(lpDrawItemStruct->hDC))
		return;

	COLORREF rgbTextColor = dc.GetTextColor();
	COLORREF rgbBkColor = dc.GetBkColor();

	if (lpDrawItemStruct->itemAction & ODA_FOCUS)
	{
		dc.DrawFocusRect(&lpDrawItemStruct->rcItem);
	}
	else if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{
		if (lpDrawItemStruct->itemState & ODS_FOCUS)
			dc.DrawFocusRect(&lpDrawItemStruct->rcItem);
		else
			dc.ExtTextOut(0, 0, ETO_OPAQUE, &lpDrawItemStruct->rcItem, _T(""), 0, NULL);
	}

	if (0 <= (int)lpDrawItemStruct->itemID)	// Any item selected?
	{
		::InflateRect(&lpDrawItemStruct->rcItem, -2, -2);

		if( (COLORREF)lpDrawItemStruct->itemData == 0xFFFFFFFF )
		{
			CSize	textSize = dc.GetTextExtent( _T("default") );
			dc.FillSolidRect( &lpDrawItemStruct->rcItem, RGB( 0xFF, 0xFF, 0xFF ) );
			dc.FrameRect( &lpDrawItemStruct->rcItem, &brushBlack );

			dc.SetTextColor( RGB( 0x00, 0x00, 0x00 ) );
			dc.SetBkColor( RGB( 0xFF, 0xFF, 0xFF ) );
			dc.SetTextAlign( TA_CENTER | TA_TOP | TA_NOUPDATECP );
			dc.TextOut( 
				lpDrawItemStruct->rcItem.left + (lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left) / 2, 
				lpDrawItemStruct->rcItem.top +
					((lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top) / 2) -
					(textSize.cy / 2), 
				_T("default") );
		}
		else
		{
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, (COLORREF)lpDrawItemStruct->itemData);
			dc.FrameRect(&lpDrawItemStruct->rcItem, &brushBlack);
		}
	}

	// Restore the DC state
	dc.SetTextColor(rgbTextColor);
	dc.SetBkColor(rgbBkColor);
	dc.Detach();
}