	void		OnDragging( CPoint& point ){
		if( m_bDragging )
		{
			CPoint	pt(point);
			ClientToScreen( &pt );
			m_pDragImage->DragMove( pt );
			m_pDragImage->DragShowNolock( FALSE );

			CWnd* pDropWnd	= CWnd::WindowFromPoint( pt );
			ASSERT(pDropWnd);

			if( pDropWnd != m_pDropWnd )
			{
				if( m_hDropItem )
				{
					((CTreeCtrl*)m_pDropWnd)->SelectDropTarget( NULL );
					m_hDropItem = NULL;
				}

				if( m_nDropIndex != -1 )
				{
					CListCtrl* pList	= (CListCtrl*)m_pDropWnd;
					pList->SetItemState( m_nDropIndex, 0, LVIS_DROPHILITED );
					pList->RedrawItems( m_nDropIndex, m_nDropIndex );
					pList->UpdateWindow();
					m_nDropIndex = -1;
				}
			}

			m_pDropWnd	= pDropWnd;
			pDropWnd->ScreenToClient( &pt );

			if( pDropWnd->IsKindOf(RUNTIME_CLASS(CTreeCtrl)) )
			{			
				UINT uFlags;
				m_hDropItem		= ((CTreeCtrl*)pDropWnd)->HitTest( pt, &uFlags );
				((CTreeCtrl*)pDropWnd)->SelectDropTarget( m_hDropItem );
			}
			else
			if( pDropWnd->IsKindOf(RUNTIME_CLASS(CListCtrl)) )
			{			
				UINT uFlags;
				CListCtrl* pList	= (CListCtrl*)pDropWnd;

				pList->SetItemState( m_nDropIndex, 0, LVIS_DROPHILITED );
				pList->RedrawItems( m_nDropIndex, m_nDropIndex );

				m_nDropIndex	= ((CListCtrl*)pDropWnd)->HitTest( pt, &uFlags );

				pList->SetItemState( m_nDropIndex, LVIS_DROPHILITED, LVIS_DROPHILITED );
				pList->RedrawItems( m_nDropIndex, m_nDropIndex );
				pList->UpdateWindow();
			}

			m_pDragImage->DragShowNolock( TRUE );
		}
	}