void COrderListBoxItem::PaintItem(COwnerDrawListBox* pList, CDC* pDC, LPDRAWITEMSTRUCT pDrawItemStruct, CRect& crBounds, COLORREF clForeground, COLORREF clBackground)
{
	CProductItem* pItem = Item();
	
	if (pItem != NULL)
	{
		CRect crListBox;
		pList->GetWindowRect(crListBox);
		
		CWnd* pDialog = pList->GetParent();
		
		CWnd* pPriceAlign = pDialog->GetDlgItem(IDC_PRICE_ALIGN);
		CRect crPriceAlign;
		pPriceAlign->GetWindowRect(crPriceAlign);
		
		CWnd* pExtensionAlign = pDialog->GetDlgItem(IDC_EXTENSION_ALIGN);
		CRect crExtensionAlign;
		pExtensionAlign->GetWindowRect(crExtensionAlign);
		
		CString csName = pItem->Name();
		
//		if (Indent() == 0)
//		{
//			csName += " *";
//		}

		int nNameAlign = crBounds.left;
		BOOL fFree = pItem->TestFlag(PRODUCT_ITEM_Free);
		LPCSTR szZero = fFree ? "Free" : "";

		CString csPrice;
		Util::PriceString(csPrice, pItem->Price(), TRUE, szZero);
		int nPriceAlign = crPriceAlign.left-crListBox.left-pDC->GetTextExtent(csPrice, csPrice.GetLength()).cx;
		
		CString csExtension = "";
		Util::PriceString(csExtension, pItem->Price(), TRUE, szZero);
		int nExtensionAlign = crExtensionAlign.left-crListBox.left-pDC->GetTextExtent(csExtension, csExtension.GetLength()).cx;
		
		COLORREF clOldForeground = pDC->SetTextColor(clForeground);
		COLORREF clOldBackground = pDC->SetBkColor(clBackground);
	
		pDC->TextOut(nNameAlign,  crBounds.top, csName,  csName.GetLength());

		if (fFree && !pItem->TestFlag(PRODUCT_ITEM_Licensed))
		{
		/* "Free" should be red. */
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		pDC->TextOut(nPriceAlign, crBounds.top, csPrice, csPrice.GetLength());
		
		if (Select())
		{
			pDC->TextOut(nExtensionAlign, crBounds.top, csExtension, csExtension.GetLength());
		}
		
		pDC->SetTextColor(clOldForeground);
		pDC->SetBkColor(clOldBackground);
	}
}