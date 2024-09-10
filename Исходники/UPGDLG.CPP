void CUpgradeDialog::DrawPrice(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	int nContext = 0;
	
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	
	if (pDC != NULL)
	{
		if ((nContext = pDC->SaveDC()) != 0)
		{
			CRect crItem(lpDrawItemStruct->rcItem);

			Util::DrawClientBorder(*pDC, crItem);

			CBrush cbBackground(GetSysColor(COLOR_WINDOW));
			pDC->FillRect(crItem, &cbBackground);
			
			CWnd* pWindow = GetDlgItem(lpDrawItemStruct->CtlID);
			CRect crWindow;
			pWindow->GetWindowRect(crWindow);
			
			CWnd* pPriceAlign = GetDlgItem(IDC_EXTENSION_ALIGN);
			CRect crPriceAlign;
			pPriceAlign->GetWindowRect(crPriceAlign);
			
			char szPrice[32];
			GetDlgItemText(lpDrawItemStruct->CtlID, szPrice, sizeof(szPrice));
			CSize czExtent = pDC->GetTextExtent(szPrice, lstrlen(szPrice));
			int nPriceAlign = crPriceAlign.left-crWindow.left-czExtent.cx;
			int nTopAlign = crItem.top+(crItem.Height()-czExtent.cy)/2;
			
			pDC->SetBkMode(TRANSPARENT);
			pDC->TextOut(nPriceAlign, nTopAlign, szPrice, lstrlen(szPrice));
			
			pDC->RestoreDC(nContext);
		}
	}
}