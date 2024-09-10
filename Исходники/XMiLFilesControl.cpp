HRESULT __stdcall CXMiLFilesControl::OnItemClick(DWORD item)
{
#if 0
	HGLOBAL hData = BuildSelectedFilesClipboard();
	if (hData)
	{
		CMyDropSource*  dropSource = new CMyDropSource;
		CMyDataObject* dataObject = new CMyDataObject;

		STGMEDIUM	stg = {0};
		stg.tymed = TYMED_HGLOBAL;
		stg.hGlobal = hData;
		stg.pUnkForRelease = NULL;
		
		FORMATETC	etc = {0};
		etc.cfFormat = CF_HDROP;//CF_UNICODETEXT;//49285;//RegisterClipboardFormat(CFSTR_SHELLURL);//CF_TEXT;
		etc.tymed = TYMED_HGLOBAL;
		etc.ptd = NULL;
		etc.dwAspect = DVASPECT_CONTENT;
		etc.lindex = -1;

		dataObject->SetData(&etc, &stg, TRUE);

		DWORD dropEffect = 0;
		HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

		if (hr == DRAGDROP_S_DROP)
		{
			if (dropEffect/* & DROPEFFECT_MOVE*/)
			{
			}
		}

		GlobalFree(hData);

	//	delete dataObject;
	//	delete dropSource;

#if 0
		COleDataSource source;
		source.CacheGlobalData(CF_HDROP, hData, NULL);

		if (source.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, NULL, NULL) == DROPEFFECT_COPY)
		{
		}

		source.Empty();
#endif
					
		GlobalFree(hData);
	}
#endif

	return S_OK;
}