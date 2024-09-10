int CPropertyForm::AnalyzeDMO(IUnknown *obj)
{
	CComPtr<IMediaObject>			dmo;
	HRESULT							hr;

	hr = obj->QueryInterface(IID_IMediaObject, (void**)&dmo);
	if (FAILED(hr)) return -1;

	// fine - it's a DMO object. now check what kind of it is.
	int						i = 0;
	int						dmo_type = -1;			// unknown
	DMO_MEDIA_TYPE			dmt;
	memset(&dmt, 0, sizeof(dmt));

	// first check if it is connected
	hr = dmo->GetInputCurrentType(0, &dmt);
	if (FAILED(hr)) {
	
		// or try to enumerate through the types
		while (dmo_type == -1) {
			hr = dmo->GetInputType(0, i++, &dmt);
			if (hr == NOERROR) {

				// currently we're only interested in WMA Decoder
				if (dmt.majortype == MEDIATYPE_Audio &&
					(
						dmt.subtype		== GraphStudio::MEDIASUBTYPE_WMA9_00 ||
						dmt.subtype		== GraphStudio::MEDIASUBTYPE_WMA9_01 ||
						dmt.subtype		== GraphStudio::MEDIASUBTYPE_WMA9_02 ||
						dmt.subtype		== GraphStudio::MEDIASUBTYPE_WMA9_03
					)
					){
					dmo_type = 0;			// WMA
				}
			}
			MoFreeMediaType(&dmt);
		}
	} else {

		// currently we're only interested in WMA Decoder
		if (dmt.majortype == MEDIATYPE_Audio &&
			(
				dmt.subtype		== GraphStudio::MEDIASUBTYPE_WMA9_00 ||
				dmt.subtype		== GraphStudio::MEDIASUBTYPE_WMA9_01 ||
				dmt.subtype		== GraphStudio::MEDIASUBTYPE_WMA9_02 ||
				dmt.subtype		== GraphStudio::MEDIASUBTYPE_WMA9_03
			)
			){
			dmo_type = 0;			// WMA
		}

		MoFreeMediaType(&dmt);
	}

	CComPtr<IPropertyPage>	page;

	switch (dmo_type) {
	case 0:
		{
			CWMADecPage	*wma_page;
			wma_page = new CWMADecPage(NULL, &hr, _T("WMA Decoder"));
			if (wma_page) {
				wma_page->AddRef();

				hr = wma_page->QueryInterface(IID_IPropertyPage, (void**)&page);
				if (SUCCEEDED(hr)) {
					hr = page->SetObjects(1, &obj);
					if (SUCCEEDED(hr)) {
						container->AddPage(page);
					}
				}
				page = NULL;

				wma_page->Release();
			}
		}
		break;
	}

	return 0;
}