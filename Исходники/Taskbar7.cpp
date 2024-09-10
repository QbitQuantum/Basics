STDMETHODIMP CTaskbar7::DeleteList(BSTR appID)
{
	if (CComBSTR(appID) == CComBSTR(""))
		return CCOMError::DispatchError(INDEX_SIZE_ERR, CLSID_Taskbar7, _T("Error deleting list!"), "appID cannot be NULL or empty", 0, NULL);

	// Do nothing on XP & Vista
	if (!m_isWindows7)
		return S_OK;

	USES_CONVERSION;
	/*HRESULT hr = */m_pCustomDestinationList->DeleteList(OLE2W(appID));

	return S_OK;
}