void COXLayoutManager::SetDefaultConstraint(UINT nChildWnd)
{
	ASSERT(m_pContainerWnd);
	
	CWnd* pWnd = m_pContainerWnd->GetDlgItem(nChildWnd);
	ASSERT(pWnd);
	if (pWnd == NULL)
	{
		TRACE0("COXLayoutManager::SetDefaultConstraint(): failed. Default constraint can only be applied after window has been created.\r\n");
		return;
	}

	CRect rect;
	pWnd->GetWindowRect(rect);
	m_pContainerWnd->ScreenToClient(rect);

	SetConstraint(nChildWnd, OX_LMS_TOP, OX_LMT_SAME, rect.top);
	SetConstraint(nChildWnd, OX_LMS_LEFT, OX_LMT_SAME, rect.left);
	RemoveConstraint(nChildWnd, OX_LMS_BOTTOM);
	RemoveConstraint(nChildWnd, OX_LMS_RIGHT);
}