void CxViewExt::OnDestroy()
{
	if (m_pViewData == NULL) goto Label_CView_Destroy;

	CWnd * pWnd = reinterpret_cast < CWnd * > ( m_pViewData->m_dwExData );
	if ( pWnd == NULL ) goto Label_CView_Destroy;
	if ( ! ::IsWindow( pWnd->GetSafeHwnd() ) ) goto Label_CView_Destroy;

	pWnd->DestroyWindow();
	delete pWnd;
	m_pViewData->m_dwExData = NULL;

Label_CView_Destroy:
	CView::OnDestroy();
}