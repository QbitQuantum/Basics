STDMETHODIMP CXRecords::GetRows(VARIANT key, VARIANT* pVal)
{
	if(!m_pFields)return SetErrorInfo(s_errInit);

	CComSafeArray<VARIANT> bstrArray;
	VARIANT* pVar;
	HRESULT hr;
	int i = 0;
	int pos;
	int count = m_listRecords->GetCount();

	pos = m_pFields->FindField(key);
	if(pos < 0 || pos >= (int)m_pFields->GetCount())
		return DISP_E_BADINDEX;

	hr = bstrArray.Create(count);
	if(FAILED(hr))return hr;

	pVar = (VARIANT*)bstrArray.m_psa->pvData;

	for(i = 0; i < count; i ++)
	{
		hr = VariantCopy(&pVar[i], (VARIANT*)&m_listRecords->GetValue(i)->m_arrayVariant[pos]);
		if(FAILED(hr))
		{
			bstrArray.Destroy();
			return hr;
		}
	}

	pVal->vt = VT_ARRAY | VT_VARIANT;
	pVal->parray = bstrArray.Detach();

	return S_OK;
}