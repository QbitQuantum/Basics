HRESULT CSimpleDropTarget::Revoke()
{
	if (m_hWndRegistered)
	{
		RevokeDragDrop(m_hWndRegistered);
		m_hWndRegistered=NULL;
	}

	return S_OK;
}