STDMETHODIMP CFDMDownload::get_Url(BSTR *pVal)
{
	USES_CONVERSION;
	*pVal = SysAllocString (T2W (m_strUrl));
	return S_OK;
}