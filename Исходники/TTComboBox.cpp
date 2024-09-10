void CTTComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CRect rc;
	GetWindowRect(&rc);
	rc.bottom -= 15;
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
	CString strText;
	// If there are no list box items, skip this message. 
	if ((int)lpDrawItemStruct->itemID < 0 || (int)lpDrawItemStruct->itemID > (GetCount()-1) )
		return;
	this->GetLBText(lpDrawItemStruct->itemID, strText);
	CDC dc;

	dc.Attach(lpDrawItemStruct->hDC);

	// Save these value to restore them when done drawing.
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();

	// The item maybe disabled...
	BOOL bDisabledItem = FALSE;
	for (int i = 0; i < m_arrDisabledItems.GetSize(); i++)
	{
		if (lpDrawItemStruct->itemID == m_arrDisabledItems.GetAt(i))
		{
			bDisabledItem = TRUE;
			break;
		}
	}   

	// If this item is selected, set the background color 
	// and the text color to appropriate values. Erase
	// the rect by filling it with the background color.
	if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
	  (lpDrawItemStruct->itemState  & ODS_SELECTED) && bDisabledItem == FALSE)
	{
	  dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	  dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
	  dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
	}
	else
	{
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
	}

	if (lpDrawItemStruct->itemState & ODS_DISABLED)
	{
		dc.SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
	}

	// Draw the text.
	dc.DrawText(
	  strText,
	  &lpDrawItemStruct->rcItem,
	  DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);

	// Reset the background color and the text color back to their
	// original values.
	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);

	dc.Detach();
}