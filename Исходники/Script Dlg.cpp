void CClassListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	 //CRect members to store the position of the items
	CRect rItem;
	CDC* dc = CDC::FromHandle(lpDrawItemStruct->hDC);

	if ((int)lpDrawItemStruct->itemID < 0)
	{
		// If there are no elements in the CListBox
		// based on whether the list box has Focus  or not
		// draw the Focus Rect or Erase it,
		if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && (lpDrawItemStruct->itemState & ODS_FOCUS))
		{
			dc->DrawFocusRect(&lpDrawItemStruct->rcItem);
		}
		else if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && !(lpDrawItemStruct->itemState & ODS_FOCUS))
		{
			dc->DrawFocusRect(&lpDrawItemStruct->rcItem);
		}
		   return;
	}


	// String to store the text
	CString strText;

	// Get the item text.
	GetText(lpDrawItemStruct->itemID, strText);

	//Initialize the CListBox Item's row size
	rItem = lpDrawItemStruct->rcItem;

	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
	if (GetStyle() & LBS_USETABSTOPS)
	nFormat |= DT_EXPANDTABS;


	// If CListBox item selected, draw the highlight rectangle.
	// Or if CListBox item deselected, draw the rectangle using the window color.
	bool ItemSelected = (lpDrawItemStruct->itemState & ODS_SELECTED);
	bool ItemChecked = (lpDrawItemStruct->itemState & ODS_CHECKED);

	COLORREF crBG = RGB(255,255,255);
	COLORREF crText = RGB(0,0,255);

	if (ItemSelected)
	{
		crBG = crText;
		crText = 0xffffff;	
	}

	CBrush br(crBG);
	dc->FillRect(&rItem, &br);

	


	// If the CListBox item has focus, draw the focus rect.
	// If the item does not have focus, erase the focus rect.
	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && (lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		dc->DrawFocusRect(&rItem);
	}
	else if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && !(lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		dc->DrawFocusRect(&rItem);
	}

	// To draw the Text in the CListBox set the background mode to Transparent.
	int iBkMode = dc->SetBkMode(TRANSPARENT);

	CFont font;
	font.CreatePointFont(100,"Courier New");

	dc->SetTextColor(crText);
	dc->SelectObject(&font);

	//Draw the Text
	dc->TextOut(rItem.left,rItem.top,strText);

}