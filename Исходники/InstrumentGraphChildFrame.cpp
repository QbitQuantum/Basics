/**
* 响应上工具条按钮；选择测试类型
* @param void
* @return void
*/
void CInstrumentGraphChildFrame::OnSelectTestType() 
{
	CInstrumentGraphView* pView = (CInstrumentGraphView*)GetActiveView();

	CBCGPToolbarComboBoxButton* pComboButton = NULL;
	pComboButton = (CBCGPToolbarComboBoxButton*)m_oGraphViewTopToolBar.GetButton(12);
	m_strTestType = pComboButton->GetText();
	m_uiTestType = m_pSiteData->GetTestTypeIDByString(m_strTestType);
	if(30 != m_uiTestType)
	{
		// 得到仪器TestType判据字符串
		m_strTestType = m_pSiteData->GetInsarumentTestTypeLimitStringByID(m_uiTestType);
	}
	CToolbarGraph* pBNGraph = NULL;
	pBNGraph = (CToolbarGraph*)m_oGraphViewTopToolBar.GetButton(7);
	pBNGraph->m_iMode = 1;
	pBNGraph->m_strLabel = m_strTestType;
	m_oGraphViewTopToolBar.InvalidateButton(7);

	pView->RedrawWindow();
}