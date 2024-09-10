void COleDropTarget::Revoke()
{
	ASSERT_VALID(this);
	ASSERT(m_lpDataObject == NULL);

	if (m_hWnd == NULL)
	{
		ASSERT(m_nTimerID == 0xffff);
		return;
	}

	// disconnect from OLE
	RevokeDragDrop(m_hWnd);
	CoLockObjectExternal((LPUNKNOWN)GetInterface(&IID_IUnknown), FALSE, TRUE);

	// disconnect internal data
	CWnd::FromHandle(m_hWnd)->m_pDropTarget = NULL;
	m_hWnd = NULL;
}