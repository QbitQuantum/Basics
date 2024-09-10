LRESULT
CCPApplet::OnRun(CWnd* pParentWnd)
{
	LRESULT		lResult = 1;
	CWnd	*	pWnd;

	InitCommonControls();

	pWnd = (CWnd*) m_uiClass->CreateObject(); 

	if ( pWnd )
	{
		lResult = ERROR_SUCCESS;

		if ( pWnd->IsKindOf( RUNTIME_CLASS( CPropertySheet ) ) )
		{
			CPropertySheet * pSheet = (CPropertySheet*) pWnd;

			pSheet->Construct(m_name, pParentWnd, m_pageNumber);

			pSheet->DoModal();
		}
		else
		{
			check( pWnd->IsKindOf( RUNTIME_CLASS( CDialog ) ) );

			CDialog * pDialog = (CDialog*) pWnd;

      		pDialog->DoModal();
    	}

		delete pWnd;
  	}

	return lResult;
}