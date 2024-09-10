BOOL COrderByMailDialog::OnInitDialog()
{
	CenterWindow();
	
	CBaseDialog::OnInitDialog();

	CMlsPropertyControl::SubclassPropertyControls(this);

	// Build the product list and get some prices.
	
	m_pInfo->GetLRCFromProducts(m_csLRC);

	m_CodeCtrl.LimitText(12);

	BOOL fProductsOrdered = GetApp()->Offer()->CountProductFlags(PRODUCT_ITEM_Selected) > 0;
	
	CWnd* pWnd = GetDlgItem(IDC_PRINTORDERFORM);
	
	if (pWnd != NULL)
	{
		pWnd->EnableWindow(fProductsOrdered);
	}

	CWnd* pFocus = GetDlgItem(fProductsOrdered ? IDC_PRINTORDERFORM : IDC_ACCESS_CODE);
	
	if (pFocus != NULL)
	{
		pFocus->SetFocus();
	}

	return pFocus == NULL;
}