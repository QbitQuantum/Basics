void CBasePropertySheet::AddPage(CPropertyPage* pPage)
{
	ASSERT_VALID(this);
	ASSERT(pPage != NULL);
	ASSERT_KINDOF(CPropertyPage, pPage);
	ASSERT_VALID(pPage);

	// add page to internal list
	m_pages.Add(pPage);

	// add page externally
	if (m_hWnd != NULL)
	{
		// build new prop page array
		AFX_OLDPROPSHEETPAGE *ppsp = new AFX_OLDPROPSHEETPAGE[m_pages.GetSize()];
		memcpy(ppsp, m_psh.ppsp, sizeof(AFX_OLDPROPSHEETPAGE) * (m_pages.GetSize()-1));
		delete[] (PROPSHEETPAGE*)m_psh.ppsp;
		m_psh.ppsp = (PROPSHEETPAGE*)ppsp;
		ppsp += m_pages.GetSize()-1;

		// copy processed PROPSHEETPAGE struct to end
		memcpy(ppsp, &pPage->m_psp, sizeof(pPage->m_psp));
//		pPage->PreProcessPageTemplate((PROPSHEETPAGE&)*ppsp, IsWizard());
		CPropertyPage_PreProcessPageTemplate((_CCPropertyPage*)pPage, (PROPSHEETPAGE&)*ppsp, IsWizard());
		HPROPSHEETPAGE hPSP = CreatePropertySheetPage((PROPSHEETPAGE*)ppsp);
		if (hPSP == NULL)
			AfxThrowMemoryException();

		if (!SendMessage(PSM_ADDPAGE, 0, (LPARAM)hPSP))
		{
			DestroyPropertySheetPage(hPSP);
			AfxThrowMemoryException();
		}
	}
}