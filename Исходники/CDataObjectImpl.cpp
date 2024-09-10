STDMETHODIMP CDataObject::GetData(FORMATETC *pFormatEtc, STGMEDIUM *pStgMedium)
{
	LONG idx = LookupFormatEtc(pFormatEtc);
	if (idx  == -1)
	{
		return DV_E_FORMATETC;
	}

	memset(pStgMedium, 0, sizeof(STGMEDIUM));

	if(m_vtFtmEtc[idx].tymed != TYMED_NULL)
	{
		if (!CopyStgMedium(pFormatEtc->cfFormat, pStgMedium, &m_vtStgMedium[idx]))
		{
			ATLTRACE(L"\nGetData: %d, hr=%x", pFormatEtc->cfFormat, DATA_E_FORMATETC);

			return DATA_E_FORMATETC;
		}

		ATLTRACE(L"\nGetData: %d, hr=%x", pFormatEtc->cfFormat, 0);

		return S_OK;
	}

	ATLTRACE(L"\nGetData: %d, hr=%x", pFormatEtc->cfFormat, DATA_E_FORMATETC);

	return DATA_E_FORMATETC;
}