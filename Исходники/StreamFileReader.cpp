void StreamFileReader::Open(CStdStringW sDocFileName)
{
	HRESULT hr = StgOpenStorage(sDocFileName ,NULL, STGM_DIRECT_SWMR|STGM_READ|STGM_SHARE_DENY_NONE,
		NULL, 0, &m_pRootStorage);

	if (FAILED(hr))
		throw _com_error(hr);

	if (m_pRootStorage == NULL)
		throw _com_error(E_FAIL);
}