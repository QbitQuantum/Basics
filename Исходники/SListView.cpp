void CSListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( UPDATE_HINT_SLISTVIEW != lHint )
		return;
	if( IsWindowVisible() )
		SetFocus( );
	int	nColumnCount	=	m_Grid.GetColumnCount();
	if( nColumnCount <= 0 )
		return;

	if( GetParentFrame()->GetSafeHwnd() != AfxGetMainFrame()->GetActiveFrame()->GetSafeHwnd() )
	{
		m_bShouldUpdate	=	TRUE;
		return;
	}
	m_bShouldUpdate	=	FALSE;

	CStockContainer & container = AfxGetSListStockContainer();
	container.Lock();

	m_Grid.DeleteNonFixedRows();

	// Progress

	CUIntArray	anParams;
	anParams.SetSize( 0, nColumnCount );
	for( int nCol=0; nCol < nColumnCount; nCol ++ )
	{
		LPARAM	lParam	=	m_Grid.GetItemData( 0, nCol );
		anParams.Add( lParam );
	}

	CRect rectClient;
	GetClientRect( &rectClient );
	int nPageCount = 1 + rectClient.Height() / abs(m_Grid.GetFixedRowHeight()) + 1;
/** disabled 
	for( int i=0; i<container.GetSize(); i++ )
	{
		CStockInfo & info = container.GetStockInfoByID(i);

		int nRow = m_Grid.InsertRow( info.GetStockName() );
		m_Grid.SetItemData( nRow, 0, i );

		for( int nCol=0; nCol<anParams.GetSize(); nCol++ )
		{
			m_Grid.SetItemFormat( nRow, nCol, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
			m_Grid.SetItemText( nRow, nCol, AfxGetVariantDispString( anParams[nCol], info, &container ) );
			m_Grid.SetItemBkColour( nRow, nCol, AfxGetProfile().GetColor(CColorClass::clrSListBK) );
			m_Grid.SetItemFgColour( nRow, nCol, AfxGetVariantColor( anParams[nCol], info ) );
			if( anParams[nCol] == SLH_DATE )
				m_Grid.SetColumnWidth( nCol, 80 );
		}

		if( i == nPageCount+5 )
		{
			m_Grid.Invalidate( );
			MSG		msg;
			while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE) )
				AfxGetApp()->PumpMessage();
		}
		if( pMainFrame )
			pMainFrame->SetProgress( 100*i/container.GetSize() );
	}

	// Set Average and Weight Average
	SetAverageItem( m_Grid, container, FALSE );

	// Sort If Needed
	if( -1 != m_nColSort )
	{
		LPARAM	lParam	=	m_Grid.GetItemData( 0, m_nColSort );
		if( lParam >= 0 )
		{
			CStockContainer::m_pSortContainer	=	&container;
			container.m_nSortVariantID	=	lParam;
			container.m_bSortAscend		=	m_bSortAscend;
			m_Grid.SortItems( ItemCompareFunc, 0, TRUE );
		}
	}

*/
	for(int i= 0;i<1;i++)
	{
		int nRow = m_Grid.InsertRow( "sz002376");
		m_Grid.SetItemData( nRow, 0, i );
        const char * paramValues [] = {"新北洋","sz002376","1000","1000","1000","17.74","19.08","17740","-1340.0"};
		for( int nCol=0; nCol<9; nCol++ )
		{
			m_Grid.SetItemFormat( nRow, nCol, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
			m_Grid.SetItemText( nRow, nCol, paramValues[nCol] );
			m_Grid.SetItemBkColour( nRow, nCol, AfxGetProfile().GetColor(CColorClass::clrSListBK) );
			//m_Grid.SetItemFgColour( nRow, nCol, );
			if( anParams[nCol] == SLH_DATE )
				m_Grid.SetColumnWidth( nCol, 80 );
		}
	}

	int nRow = m_Grid.InsertRow( "summary");
	//m_Grid.SetItemData( nRow, 0, 1 );
	 const char * sumValues [] = {"","","","","","","合计(人民币)","17740","-1340.0"};
	 
	 for( int ic=0; ic<9; ic++ )
	 {
		 m_Grid.SetItemFormat( nRow, ic, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		 m_Grid.SetItemText( nRow, ic, sumValues[ic] );
		 m_Grid.SetItemBkColour( nRow, 0, AfxGetProfile().GetColor(CColorClass::clrSListBK) );
	 }

	 nRow = m_Grid.InsertRow( "blank");
	 m_Grid.SetItemText( nRow, 0, "" );
	 m_Grid.SetItemBkColour( nRow, 0, AfxGetProfile().GetColor(CColorClass::clrSListBK) );
	//m_Grid.SetItemData( nRow, 0, 1 );

	 nRow = m_Grid.InsertRow( "allheader");
	 const char * allValues [] = {"币种","资金余额","可用资金","可取资金","证券市值","资产总值","","",""};
	 for( ic=0; ic<9; ic++ )
	 {
		 m_Grid.SetItemFormat( nRow, ic, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		 m_Grid.SetItemText( nRow, ic, allValues[ic] );
		 m_Grid.SetItemBkColour( nRow, ic, AfxGetProfile().GetColor(CColorClass::clrSListBK) );
		 m_Grid.SetItemFgColour( nRow, ic, 0x00ff0000 );
		 LOGFONT *pfont = m_Grid.GetItemFont(nRow,ic);
		 pfont->lfWeight = 700;
		 m_Grid.SetItemFont(nRow,ic,pfont);
	 }

	 nRow = m_Grid.InsertRow( "alldata");
	 const char * alldataValues [] = {"人民币","2163.99","2163.99","2163.99","17740","19903.99","","",""};
	 for( ic=0; ic<9; ic++ )
	 {
		 m_Grid.SetItemFormat( nRow, ic, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		 m_Grid.SetItemText( nRow, ic, alldataValues[ic] );
		 m_Grid.SetItemBkColour( nRow, ic, AfxGetProfile().GetColor(CColorClass::clrSListBK) );
	 }



	if( m_bFirstUpdate )
		m_Grid.AutoSizeColumns( );
	else
		m_Grid.SetColumnWidth( 0, 80 );
	m_bFirstUpdate	=	FALSE;
	m_Grid.Invalidate( );

	//SendRequestQuote(TRUE);

	container.UnLock();
}