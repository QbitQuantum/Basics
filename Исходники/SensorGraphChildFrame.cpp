/**
* 响应上工具条按钮；选择检波器Nb
* @param void
* @return void
*/
void CSensorGraphChildFrame::OnSelectSensorNb() 
{
	CSensorGraphView* pView = (CSensorGraphView*)GetActiveView();

	CBCGPToolbarComboBoxButton* pComboButton = NULL;
	int iCurSel = 0;
	pComboButton = (CBCGPToolbarComboBoxButton*)m_oGraphViewTopToolBar.GetButton(6 + m_uiSensorNbCount);
	iCurSel = pComboButton->GetCurSel();
	m_uiSensorNb = pComboButton->GetItemData(iCurSel);

	pView->RedrawWindow();
}