void COleClientItem::OnActivate()
{
	ASSERT_VALID(this);

	// it is necessary to lock the object when it is in-place
	//  (without this, a link to an embedding may disconnect unexpectedly)
	if (!m_bLocked)
	{
		OleLockRunning(m_lpObject, TRUE, FALSE);
		m_bLocked = TRUE;
	}

	// notify the item of the state change
	if (m_nItemState != activeState)
	{
		OnChange(OLE_CHANGED_STATE, (DWORD)activeState);
		m_nItemState = activeState;
	}
}