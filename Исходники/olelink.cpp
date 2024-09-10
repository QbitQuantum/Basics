void COleLinkingDoc::Revoke()
{
	ASSERT_VALID(this);

	// revoke current registration
	if (m_dwRegister != 0)
	{
		LPRUNNINGOBJECTTABLE lpROT = NULL;
		GetRunningObjectTable(0, &lpROT);
		if (lpROT != NULL)
		{
			lpROT->Revoke(m_dwRegister);
			lpROT->Release();
		}
		m_dwRegister = 0;
	}
	RELEASE(m_lpMonikerROT);
	m_strMoniker = _T("");
}