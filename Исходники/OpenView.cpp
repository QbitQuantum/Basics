void COpenView::OnDestroy()
{
	if (m_pDropHandler)
		RevokeDragDrop(m_hWnd);

	m_constraint.Persist(true, false);

	CFormView::OnDestroy();
}