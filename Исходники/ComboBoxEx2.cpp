void UpdateHorzExtent(CComboBox &rctlComboBox, int iIconWidth)
{
	int iItemCount = rctlComboBox.GetCount();
	if (iItemCount > 0)
	{
		CDC *pDC = rctlComboBox.GetDC();
		if (pDC != NULL)
		{
			// *** To get *ACCURATE* results from 'GetOutputTextExtent' one *MUST*
			// *** explicitly set the font!
			CFont *pOldFont = pDC->SelectObject(rctlComboBox.GetFont());

			CString strItem;
			int iMaxWidth = 0;
			for (int i = 0; i < iItemCount; i++)
			{
				rctlComboBox.GetLBText(i, strItem);
				int iItemWidth = pDC->GetOutputTextExtent(strItem, strItem.GetLength()).cx;
				if (iItemWidth > iMaxWidth)
					iMaxWidth = iItemWidth;
			}
			
			pDC->SelectObject(pOldFont);
			rctlComboBox.ReleaseDC(pDC);

			// Depending on the string (lot of "M" or lot of "i") sometime the
			// width is just a few pixels too small!
			iMaxWidth += 4;
			if (iIconWidth)
				iMaxWidth += 2 + iIconWidth + 2;
			rctlComboBox.SetHorizontalExtent(iMaxWidth);
			if (rctlComboBox.GetDroppedWidth() < iMaxWidth)
				rctlComboBox.SetDroppedWidth(iMaxWidth);
		}
	}
	else
		rctlComboBox.SetHorizontalExtent(0);
}