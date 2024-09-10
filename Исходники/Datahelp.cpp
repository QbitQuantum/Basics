// Lesen eines EnumLONG aus einem DataObjekt ----------------------------------
HRESULT GetHWNDData (IDataObject *pIDataObj, HWND *phWnd)
{
HRESULT hr = E_FAIL;
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try {
	// Testen, ob das gewünschte Format überhaupt da ist
		THROW_FAILED_HRESULT(pIDataObj -> QueryGetData ((FORMATETC *)&c_feObjectWindow));

	// Daten vom DataObject geben lassen
		THROW_FAILED_HRESULT(pIDataObj -> GetData ((FORMATETC *)&c_feObjectWindow, &stg));

	// HWND aus STGMEDIUM herauskopieren
	HWND *phWndGlobal = (HWND *)GlobalLock (stg.hGlobal);

		if (NULL == phWndGlobal)
			_com_issue_error(E_UNEXPECTED);

		*phWnd = *phWndGlobal;
		ReleaseStgMedium (&stg);

	} catch (_com_error &e) {
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR(e);
	}	
	return NOERROR;
}