LRESULT CStroeSet::PopulateComboList(WPARAM wParam, LPARAM lParam)
{
	// Get the Combobox window pointer
	CComboBox* pInPlaceCombo = static_cast<CComboBox*> (GetFocus());
	//去掉排序属性
	// 	DWORD nStyle   =   GetWindowLong(pInPlaceCombo->m_hWnd,GWL_STYLE);   
	// 	nStyle   =   nStyle &(~ LBS_SORT);   
	// 	SetWindowLong(pInPlaceCombo->m_hWnd,GWL_STYLE,nStyle);   

	CRect obWindowRect;
	pInPlaceCombo->GetWindowRect(&obWindowRect);
	//pInPlaceCombo->MoveWindow(obWindowRect.left,obWindowRect.top,obWindowRect.Width(),500);
	CPoint obInPlaceComboTopLeft(obWindowRect.TopLeft()); 
	// Get the active list
	// Get the control window rect
	// If the inplace combobox top left is in the rect then
	// The control is the active control
	m_List.GetWindowRect(&obWindowRect);

	int iColIndex = wParam;
	CStringList* pComboList = reinterpret_cast<CStringList*>(lParam);
	pComboList->RemoveAll();
	if (obWindowRect.PtInRect(obInPlaceComboTopLeft)) 
	{
		if (1 == iColIndex)
		{
			InitComString(pComboList);
		}		
	}
	return 0;
}