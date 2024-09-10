HRESULT CRMrender::CreateFactory()
{
	HRESULT hr = S_FALSE;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDisplayFactory);

	return hr;
}