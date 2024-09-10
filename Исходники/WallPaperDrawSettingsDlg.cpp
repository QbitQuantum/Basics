/*
	OnSelchangingTree()
*/
void CWallPaperDrawSettingsDlg::OnSelchangingTree(NMHDR* /*pNMHDR*/,LRESULT* pResult)
{
	if(m_bCreated)
	{
		HTREEITEM hCurrent = m_wndSettingsTree.GetSelectedItem();
		if(hCurrent)
		{
			CPropertyPage* pPropertyPage = (CPropertyPage*)m_wndSettingsTree.GetItemData(hCurrent);
			if(pPropertyPage)
				pPropertyPage->ShowWindow(SW_HIDE);
		}
	}

	*pResult = 0;
}