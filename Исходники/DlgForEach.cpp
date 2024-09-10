void CDlgForEach::InitGrid()
{
	CWnd* wndGrid = GetDlgItem(IDC_STATIC_GRID);
	CRect rc;
	wndGrid->GetClientRect (&rc);
	wndGrid->MapWindowPoints (this, &rc);
	wndGrid->ShowWindow(SW_HIDE);
	rc.DeflateRect(1, 1, 1, 1);

	m_forEachGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/, rc, this, (UINT)-1);
	m_forEachGrid.EnableColumnAutoSize (TRUE);
	m_forEachGrid.SetSingleSel (TRUE);
	m_forEachGrid.EnableGroupByBox (FALSE);
	m_forEachGrid.SetReadOnly (TRUE);
	m_forEachGrid.SetWholeRowSel (TRUE);
	m_forEachGrid.EnableHeader (FALSE);

	//m_forEachGrid.SetWindowPos (&CWnd::wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	//m_forEachGrid.SetScrollBarsStyle(CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);

	//设置颜色
	CBCGPGridColors theme;
	CBCGPVisualManager::GetInstance ()->OnSetGridColorTheme (&m_forEachGrid, theme);
	theme.m_clrBackground = RGB(251, 251, 251);
	theme.m_HeaderSelColors.InitColors();

	m_forEachGrid.SetColorTheme (theme);

	//初始化列
	int nColCount = 1;
	for (int i=0; i<nColCount; i++)
	{
		m_forEachGrid.SetColumnAlign(i, HDF_CENTER);
	}
	m_forEachGrid.AdjustLayout ();

// 	const int nColumns = m_forEachGrid.GetColumnCount ();
// 
// 	m_relatedGrid.RemoveAll();
// 
// 	for(int i = 0; i < nCount; i++)
// 	{
// 		ZTreeParam* pParam = (ZTreeParam*)m_wndGridTree.GetRow(i)->GetData();
// 		if(pParam && pParam->m_pRelatedParam)
// 		{//存在关联
// 			CBCGPGridRow * pRow = NULL;
// 			pRow = m_relatedGrid.CreateRow (nColumns);
// 
// 			pRow->GetItem (COL_NAME1)->SetValue ( (LPCTSTR)pParam->m_strName.c_str() );
// 			CString str = pParam->m_strType.c_str();
// 			str.Replace("Int", "Integer");
// 			pRow->GetItem (COL_TYPE)->SetValue ( str.GetBuffer() );
// 			//pRow->GetItem (COL_TYPE)->SetValue ( (LPCTSTR)pParam->m_strType.c_str() );
// 			pRow->GetItem (COL_NAME2)->SetValue ( (LPCTSTR)pParam->m_pRelatedParam->m_strName.c_str() );
// 			pRow->GetItem (COL_PATH)->SetValue ( (LPCTSTR)pParam->m_pRelatedParam->m_strPath.c_str() );
// 			pRow->SetData((DWORD_PTR)pParam);
// 			//pRow->ReplaceItem(COL_NAME1, new CBCGPGridCheckItem(FALSE));
// 			//m_relatedGrid.getHeader
// 			m_relatedGrid.AddRow (pRow, FALSE);
// 		}
// 	}
// 
// 	for(int i = 0; i < 100; i++)
// 	{
// 		CBCGPGridRow * pRow = NULL;
// 		pRow = m_forEachGrid.CreateRow (nColumns);
// 		CBCGPGridItem* pItem = new CBCGPGrid;
// 		pRow->ReplaceItem(
// 		m_forEachGrid.AddRow()
// 	}
}