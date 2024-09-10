void CLostCornerDlg::InitData()
{
	if (!m_pPapers) return;

	m_lcLostCornerPaper.DeleteAllItems();
	m_lcLostCornerPaper.DeleteAllItems();

	USES_CONVERSION;
	for (auto pPaper : m_pPapers->lPaper)
	{
		bool bInsert = false;
		for (auto pPic : pPaper->lPic)
		{
			if (pPic->lLostCorner.size())
			{
				if (!bInsert)
				{
					bInsert = true;
					//添加进试卷列表控件
					int nCount = m_lcLostCornerPaper.GetItemCount();
					char szCount[10] = { 0 };
					sprintf_s(szCount, "%d", pPaper->nIndex);	//nCount + 1
					m_lcLostCornerPaper.InsertItem(nCount, NULL);
					m_lcLostCornerPaper.SetItemText(nCount, 0, (LPCTSTR)A2T(szCount));
					m_lcLostCornerPaper.SetItemText(nCount, 1, (LPCTSTR)A2T(pPaper->strSN.c_str()));
					//显示备注信息，为何出现在此列表
					std::string strDetailInfo;
					strDetailInfo = Poco::format("折角%d个", (int)pPic->lLostCorner.size());
					m_lcLostCornerPaper.SetItemText(nCount, 2, (LPCTSTR)A2T(strDetailInfo.c_str()));
					m_lcLostCornerPaper.SetItemData(nCount, (DWORD_PTR)pPaper);

					CString strTips = _T("双击显示此试卷信息");
					m_lcLostCornerPaper.SetItemToolTipText(nCount, 0, (LPCTSTR)strTips);
					m_lcLostCornerPaper.SetItemToolTipText(nCount, 1, (LPCTSTR)strTips);
					m_lcLostCornerPaper.SetItemToolTipText(nCount, 2, (LPCTSTR)strTips);
				}
			}
		}		
	}
	if (m_lcLostCornerPaper.GetItemCount() > 0)
	{
		m_nCurrentPaperID = 0;
		m_lcLostCornerPaper.GetItemColors(m_nCurrentPaperID, 0, crPaperOldText, crPaperOldBackground);

		pST_PaperInfo pPaper = (pST_PaperInfo)m_lcLostCornerPaper.GetItemData(m_nCurrentPaperID);
		ShowPaperDetail(pPaper);
	}
}