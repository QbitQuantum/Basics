HRESULT InputFileData::AssignSafeArray(SAFEARRAY* psa)
{
	if (!m_sFileName.IsEmpty())
		return E_INVALIDARG;

	if (psa->cDims != 1)
		return E_INVALIDARG;

	if (psa->rgsabound[0].lLbound != 0)
		return E_INVALIDARG;

	void* pvData = NULL;
	if (FAILED(SafeArrayAccessData(psa, &pvData)))
		return E_INVALIDARG;


	m_iCharCount = psa->rgsabound[0].cElements;
	m_pBuffer = new unsigned char[m_iCharCount];
	m_bOurBuffer = true;
	memcpy(m_pBuffer, pvData, m_iCharCount);

	SafeArrayUnaccessData(psa);
	return S_OK;
}