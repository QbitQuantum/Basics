static HRESULT SavePropSeq (
	LPCSTR pcDesc, IPropertyActionSequence *pISeq, IStorage *pIStg)
{
HRESULT hr = E_FAIL;
WStorage IStg (pIStg);

	USES_CONVERSION;
	if (NULL == pIStg) {	// SubStorage anlegen, da es noch nicht existiert
	WStorage IRootStg;

		if (!DEX_GetProjectStorage(*IRootStg.ppv()))
			return E_FAIL;

		hr = IRootStg -> CreateStorage (A2OLE(g_cbPropertyChoices), 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
						0L, 0L, IStg.ppi());
		if (FAILED(hr)) return hr;

		hr = WriteClassStg (IStg, CLSID_PropertyChoice);
		if (FAILED(hr)) return hr;
	}

	try {
	WStream IStm;
	WPersistStream IPersistStm (pISeq);		// throws hr
	string strName = MakeStreamName(pcDesc);

	// Stream erzeugen
		hr = IStg -> CreateStream (A2OLE(strName.c_str()), 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 
						0L, 0L, IStm.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		hr = OleSaveToStream (IPersistStm, IStm);	// und wegschreiben
		if (FAILED(hr)) _com_issue_error(hr);

		hr = IStm -> Commit (STGC_DEFAULT);
		if (FAILED(hr)) _com_issue_error(hr);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	hr = IStg -> Commit (STGC_DEFAULT);
	if (SUCCEEDED(hr))
		DEX_SetDirtyGeoDB(true);

return hr;
}