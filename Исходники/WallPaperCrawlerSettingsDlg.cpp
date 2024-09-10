/*
	OnSelchangingTree()
*/
void CWallPaperCrawlerSettingsDlg::OnSelchangingTree(NMHDR* /*pNMHDR*/,LRESULT* pResult)
{
    if(m_bCreated)
    {
        HTREEITEM hCurrent = m_wndSettingsTree.GetSelectedItem();
        if(hCurrent)
        {
            CPropertyPage* pPropertyPage = (CPropertyPage*)m_wndSettingsTree.GetItemData(hCurrent);
            if(pPropertyPage)
            {
                if(pPropertyPage->IsKindOf(RUNTIME_CLASS(CWallPaperCrawlerSettingsDomainDlg)))
                {
                    CWallPaperCrawlerSettingsDomainDlg* pPage = (CWallPaperCrawlerSettingsDomainDlg*)pPropertyPage;
                    m_nDomainAcceptance = pPage->GetDomainAcceptance();
                    m_bIncludeSubDomains = pPage->GetIncludeSubDomains();
                    m_bDomainUseAlways = pPage->GetDomainUseAlways();
                    m_bSaveList = pPage->GetSaveList();
                }
                else if(pPropertyPage->IsKindOf(RUNTIME_CLASS(CWallPaperCrawlerSettingsParentUrlDlg)))
                {
                    CWallPaperCrawlerSettingsParentUrlDlg* pPage = (CWallPaperCrawlerSettingsParentUrlDlg*)pPropertyPage;
                    m_nParentUrlAcceptance = pPage->GetParentUrlAcceptance();
                    m_bParentUrlUseAlways= pPage->GetParentUrlUseAlways();
                    m_bSaveList = pPage->GetSaveList();
                }
                else if(pPropertyPage->IsKindOf(RUNTIME_CLASS(CWallPaperCrawlerSettingsWildcardsDlg)))
                {
                    CWallPaperCrawlerSettingsWildcardsDlg* pPage = (CWallPaperCrawlerSettingsWildcardsDlg*)pPropertyPage;
                    m_bSaveList = pPage->GetSaveList();
                }

                pPropertyPage->ShowWindow(SW_HIDE);
            }
        }
    }

    *pResult = 0;
}