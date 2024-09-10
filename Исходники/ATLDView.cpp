CATLDrawView::CATLDrawView()
{
	HRESULT hr;

	hr = CoInitialize(NULL);
	ASSERT(SUCCEEDED(hr));

	hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
		RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE, NULL);
	ASSERT(SUCCEEDED(hr));

	m_bDragging = FALSE;
	m_pDrawServ = NULL;
	m_col = RGB(255, 0, 0);
}