bool CSelectCoordSysActionDlg::PrepareResult()
{
// Selektierten Eintrag holen
HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL == hItem || m_tvCoordSystems.ItemHasChildren (hItem)) 
		return false;		// nur Childs behandeln

CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

	if (NULL == pItemData) 
		return false;

// Koordinatensystem am Parent setzen
CString strTcfName = pItemData->GetTcfName();

	COM_TRY {
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> CS;

		THROW_FAILED_HRESULT(CS.CoCreateInstance(CLSID_TRIASCS));
		THROW_FAILED_HRESULT(CS -> LoadFromFile(CComBSTR(strTcfName)));

		m_CS = CS;		// store result coordsystem

	} COM_CATCH_OP_RETURN(CantLoadCS(strTcfName), false);
	return true;
}