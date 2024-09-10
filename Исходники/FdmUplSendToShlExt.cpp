STDMETHODIMP CFdmUplSendToShlExt::DragEnter (IDataObject* pDataObj, DWORD grfKeyState,
                         POINTL pt, DWORD* pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg = { TYMED_HGLOBAL };
	HDROP hDrop;

	if (FAILED (pDataObj->GetData (&fmt, &stg)))
		return E_INVALIDARG;

	hDrop = (HDROP) GlobalLock (stg.hGlobal);

	if (hDrop == NULL)
		return E_INVALIDARG;

	int cFiles = DragQueryFile (hDrop, 0xFFFFFFFF, NULL, 0);

	if (cFiles == 0)
	{
		GlobalUnlock (stg.hGlobal);
		ReleaseStgMedium (&stg);
		return E_INVALIDARG;
	}

	for (int i = 0; i < cFiles; i++)
	{
		char szFile [MAX_PATH];
		if (0 == DragQueryFile (hDrop, i, szFile, MAX_PATH))
			continue;

		DWORD dwAttribs = GetFileAttributes (szFile);
		if (dwAttribs == DWORD (-1))
			continue;
		
		

		m_vFiles.push_back (szFile);
	}

	GlobalUnlock (stg.hGlobal);
	ReleaseStgMedium (&stg);

	if (m_vFiles.size () == 0)
		return E_INVALIDARG;

	*pdwEffect = DROPEFFECT_COPY;

	return S_OK;
}