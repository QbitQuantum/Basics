void PropertyPageHandler_BaseReloc::OnInitDialog()
{
	// Insert Tabs
	TCITEM item;

	for (int i = 0; i < m_PEReaderWriter.getNoOfBaseRelocationTables(); ++i)
	{
		item.mask = TCIF_TEXT;
		item.pszText = LPWSTR(_wcsdup(wstring(L"Table " + DWORD_toString(i + 1)).c_str()));

		TabCtrl_InsertItem(m_hTabsBaseReloc, i, &item);
		free(item.pszText);
	}

	// Insert ListView columns
	LV_COLUMN column;
	ZeroMemory(&column, sizeof(LV_COLUMN));

	for (size_t i = 0; i < ARRAYSIZE(szGenericColumnText); ++i)
	{
		column.mask = LVCF_TEXT;
		column.pszText = szGenericColumnText[i];

		ListView_InsertColumn(m_hListViewBaseRelocTable, i, &column);
	}

	tabsBaseRelocations_OnTabChanged(m_hWnd, 0);
}