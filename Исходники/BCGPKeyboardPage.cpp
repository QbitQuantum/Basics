//******************************************************************
void CBCGPKeyboardPage::OnSelchangeCategory() 
{
	UpdateData ();

	int iIndex = m_wndCategoryList.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		ASSERT (FALSE);
		return;
	}

	m_wndCommandsList.ResetContent ();
	m_wndCurrentKeysList.ResetContent ();

	CObList* pCategoryButtonsList = 
		(CObList*) m_wndCategoryList.GetItemData (iIndex);
	ASSERT_VALID (pCategoryButtonsList);

	CString strCategory;
	m_wndCategoryList.GetLBText (iIndex, strCategory);

	BOOL bAllCommands = (strCategory == m_strAllCategory);

	CClientDC dcCommands (&m_wndCommandsList);
	CFont* pOldFont = dcCommands.SelectObject (m_wndCommandsList.GetFont ());
	ASSERT (pOldFont != NULL);

	CBCGPToolbarCustomize* pWndParent = DYNAMIC_DOWNCAST (CBCGPToolbarCustomize, GetParent ());
	ASSERT (pWndParent != NULL);

	int cxCommandsExtentMax = 0;

	for (POSITION pos = pCategoryButtonsList->GetHeadPosition (); pos != NULL;)
	{
		CBCGPToolbarButton* pButton = (CBCGPToolbarButton*) pCategoryButtonsList->GetNext (pos);
		ASSERT (pButton != NULL);

		if (pButton->m_nID > 0 && pButton->m_nID != (UINT) -1)
		{
			CString strText = pButton->m_strText;

			if (!pButton->m_strTextCustom.IsEmpty () &&
				(bAllCommands || pWndParent->GetCountInCategory (strText, *pCategoryButtonsList) > 1))
			{
				strText = pButton->m_strTextCustom;
			}

			int iIndex = m_wndCommandsList.AddString (strText);
			m_wndCommandsList.SetItemData (iIndex, (DWORD_PTR) pButton);

			cxCommandsExtentMax = max (cxCommandsExtentMax, dcCommands.GetTextExtent (strText).cx);
		}
	}

	m_wndCommandsList.SetHorizontalExtent (cxCommandsExtentMax + ::GetSystemMetrics (SM_CXHSCROLL));

	dcCommands.SelectObject (pOldFont);

	m_wndNewKey.EnableWindow (FALSE);

	m_wndCommandsList.SetCurSel (0);
	OnSelchangeCommandsList ();
}