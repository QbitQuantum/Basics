BOOL CStaticDoc::ShowStaticView( CRuntimeClass * pViewClass, BOOL bMaximized )
{
	if( NULL == pViewClass )
		return FALSE;

	CChildFrame * pChildFrame = NULL;

	POSITION pos = GetFirstViewPosition( );
	CView * pView = NULL;
	while( pView = GetNextView(pos) )
	{
		if( pView->IsKindOf( pViewClass ) )
		{
			pChildFrame = DYNAMIC_DOWNCAST( CChildFrame, pView->GetParentFrame() );
			ASSERT( pChildFrame );
			if( pChildFrame )
				break;
		}
	}

	if( NULL == pChildFrame )
	{
		// create frame
		pChildFrame = CChildFrame::CreateNewFrame( this );
		ASSERT( pChildFrame );

		if( pChildFrame )
		{
			// create view
			CCreateContext context;
			context.m_pCurrentDoc = this;
			context.m_pCurrentFrame = pChildFrame;
			context.m_pLastView = NULL;
			context.m_pNewDocTemplate = NULL;
			context.m_pNewViewClass = pViewClass;

			CView * pNewView = DYNAMIC_DOWNCAST(CView,pChildFrame->CreateView( &context, AFX_IDW_PANE_FIRST));
			if( pNewView )
			{
				pChildFrame->SetActiveView( pNewView );
				pNewView->OnInitialUpdate( );
			}

			// if no active child frame, maximize this frame
			CMainFrame * pMainFrame = AfxGetMainFrame();
			if( pMainFrame )
			{
				CFrameWnd * pActiveFrame = AfxGetMainFrame()->GetActiveFrame();
				if( !pActiveFrame || !pActiveFrame->IsKindOf(RUNTIME_CLASS(CChildFrame)) )
					pChildFrame->MDIMaximize();
			}
		}
	}
	
	if( pChildFrame )
	{
		// activate it
		pChildFrame->MDIActivate();
		if( bMaximized )
			pChildFrame->MDIMaximize();
		else
			pChildFrame->ShowWindow( SW_SHOW );
	}

	return TRUE;
}