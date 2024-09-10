void CUnitDlgListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
  {
  ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);
  LPCTSTR lpszText = (LPCTSTR) lpDrawItemStruct->itemData;
  ASSERT(lpszText != NULL);
  CDC dc;

  dc.Attach(lpDrawItemStruct->hDC);

  // Save these values to restore them when done drawing.
  COLORREF crOldTextColor = dc.GetTextColor();
  COLORREF crOldBkColor = dc.GetBkColor();

  // If this item is selected, set the background color 
  // and the text color to appropriate values. Also, erase
  // rect by filling it with the background color.
  if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
    (lpDrawItemStruct->itemState & ODS_SELECTED))
  {
    dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
    dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
    dc.FillSolidRect(&lpDrawItemStruct->rcItem, 
      ::GetSysColor(COLOR_HIGHLIGHT));
  }
  else
    dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);

  // If this item has the focus, draw a red frame around the
  // item's rect.
  if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
    (lpDrawItemStruct->itemState & ODS_FOCUS))
  {
    CBrush br(RGB(255, 0, 0));
    dc.FrameRect(&lpDrawItemStruct->rcItem, &br);
  }

  // Draw the text.
  dc.DrawText(
    lpszText,
    strlen(lpszText),
    &lpDrawItemStruct->rcItem,
    /*DT_CENTER|*/DT_SINGLELINE|DT_VCENTER);

  // Reset the background color and the text color back to their
  // original values.
  dc.SetTextColor(crOldTextColor);
  dc.SetBkColor(crOldBkColor);

  dc.Detach();
  };