void cMarketImage::LoadRemoteImages( int iGroup, bool bShowPurchased, LPCSTR szOrderBy, int page, int itemsperpage, bool bThumbnailsUpdate )
{
	if ( m_pParent ) 
	{ 
		//m_pParent->m_textNoItems.ShowWindow( SW_HIDE );
		m_pParent->CancelRefresh();
	}

	for ( int i = 0; i <= MAX_ITEMS_PER_PAGE; i++ ) m_dwObjID [ i ] = 0;

	m_iItemClicked = -1;

	m_Images.DeleteImageList ( );
	m_Images.Create     ( 64, 64, ILC_COLOR32 | ILC_MASK, 1, 16 );
	//m_Images.SetBkColor ( RGB ( 255, 255, 255 ) );
	
	DeleteAllItems ( );
	SetImageList ( &m_Images, LVSIL_NORMAL );
	SetIconSpacing( 0, 130 );

	SetRedraw( FALSE );

	int iGroupID = 0;
	MarketGroup *pGroup = NULL;
	MarketObject *pObject = NULL;

	bool bIsSearch = false;
	bool bIsCart = false;
	bool bIsRoot = false;
	bool bIsItems = false;

	bool bNeedThumbnailUpdate = false;
	CString sThumbnailsNeeded = "";
	
	if ( iGroup == 0 ) bIsRoot = true;
	else if ( iGroup == -1 ) bIsSearch = true;
	else if ( iGroup == -2 ) bIsCart = true;
	else if ( iGroup == -3 ) bIsItems = true;
	else if ( iGroup == -4 ) iGroupID = -4;
	else
	{
		pGroup = MarketObject::GetGroup( iGroup );
		if ( pGroup ) iGroupID = pGroup->dwGroupID;
	}

	int imageCount = 0;
	int count = 0;

	if ( bIsRoot || bIsItems || (pGroup && pGroup->pChildGroup) )
	{
		bool bIsArtistList = false;

		MarketGroup *pChild;
		if ( pGroup ) pChild = pGroup->pChildGroup;
		else if ( bIsItems ) { pChild = MarketObject::GetGroupList(); bIsArtistList = true; }
		else if ( bIsRoot )
		{
			//main menu
			CBitmap bmpFolder;
			bmpFolder.LoadBitmap( IDB_FOLDER_ICON );

			m_Images.Add( &bmpFolder, (CBitmap*)NULL );
			imageCount++;

			CString sSearchResults = GetLanguageData( "TGC Store", "SearchResults" );
			CString sShoppingCart = GetLanguageData( "TGC Store", "ShoppingCart" );
			CString sFreeItems = GetLanguageData( "TGC Store", "FreeItems" );
			CString sOnlineItems = GetLanguageData( "TGC Store", "OnlineItems" );

			sSearchResults += "\\";
			sShoppingCart += "\\";
			sFreeItems += "\\";
			sOnlineItems += "\\";

			InsertItem ( 0, sSearchResults, 0 );
			InsertItem ( 1, sShoppingCart, 0 );
			InsertItem ( 2, sOnlineItems, 0 );
			
			SetRedraw( TRUE );
			Invalidate( );
			return;
		}

		int iGroupCount = 0;

		while ( pChild )
		{
			iGroupCount++;
			pChild = pChild->pNextGroup;
		}

		MarketGroup** pSortedGroupList = new MarketGroup* [ iGroupCount ];

		if ( pGroup ) pChild = pGroup->pChildGroup;
		else pChild = MarketObject::GetGroupList();
		iGroupCount = 0;

		while ( pChild )
		{
			pSortedGroupList [ iGroupCount ] = pChild;
			iGroupCount++;
			pChild = pChild->pNextGroup;
		}

		::sort( pSortedGroupList, pSortedGroupList + iGroupCount, cmpG );

		CBitmap bmpFolder;
		bmpFolder.LoadBitmap( IDB_FOLDER_ICON );

		m_Images.Add( &bmpFolder, (CBitmap*)NULL );
		imageCount++;

		if ( bIsArtistList )
		{
			bool bNeedImages = false;

			for( int i=0; i < iGroupCount; i++ )
			{
				CString sName = pSortedGroupList [ i ]->szName;

				EnterCriticalSection( &theApp.m_csDirectoryChanges );
				SetCurrentDirectory( theApp.m_szDirectory );
				CString path = "Files\\TGCStore\\TEMP\\Artists\\";
				path += sName;
				path += ".bmp";
				CImage image;
				HRESULT hr = image.Load( path );
				LeaveCriticalSection( &theApp.m_csDirectoryChanges );

				sName += "\\";

				if ( FAILED(hr) )
				{
					InsertItem ( count++, sName, 0 );
					bNeedImages = true;
				}
				else
				{
					CWindowDC wndDC( this );
					CDC dc;
					dc.CreateCompatibleDC( &wndDC );

					CBitmap	bitmap; bitmap.CreateBitmap( 64,64, 1, 32, NULL );
					CBitmap *oldBmp = dc.SelectObject( &bitmap );

					image.StretchBlt( dc.GetSafeHdc( ), 0,0, 64,64 );
					dc.SelectObject( oldBmp );

					m_Images.Add( &bitmap, (CBitmap*)NULL );
					InsertItem ( count++, sName, imageCount++ );
				}
			}

			if ( bNeedImages && m_pParent && !m_pParent->AreArtistIconsLoaded() ) m_pParent->SetTimer( 5, 1000, NULL );
		}
		else
		{
			for( int i=0; i < iGroupCount; i++ )
			{
				CString sName = pSortedGroupList [ i ]->szName;
				sName += "\\";
				InsertItem ( count++, sName, 0 );
			}
		}

		delete [] pSortedGroupList;
	}

	CBitmap bmpNoThumbnail;
	bmpNoThumbnail.LoadBitmap( IDB_NO_THUMBNAIL );
	m_Images.Add( &bmpNoThumbnail, (CBitmap*)NULL );
	int iNoThumbnailIcon = imageCount;
	imageCount++;

	if ( bIsSearch ) pObject = MarketObject::GetSearchList( );
	else if ( bIsCart ) pObject = MarketObject::GetCartList( );
	else pObject = MarketObject::GetObjectList( );

	int iObjCount = 0;

	while ( pObject )
	{
		if ( ( bShowPurchased || !pObject->IsPurchased() ) && ( bIsSearch || bIsCart || iGroupID == -4 || pObject->GetGroupID( ) == iGroupID ) )
		{
			iObjCount++;
		}

		pObject = pObject->pNextObject;
	}

	if ( iObjCount == 0 && count == 0 )
	{
		//InsertItem ( 0, "<No Items>", -1 );
		if ( m_pParent ) m_pParent->ShowNoItemsMsg();
		if ( m_pParent ) m_pParent->SetPageNumbers( 1,1 );

		SetRedraw( TRUE );
		Invalidate();
		m_pParent->m_textNoItems.Invalidate();
		return;
	}

	if ( iObjCount == 0 )
	{
		if ( m_pParent ) m_pParent->SetPageNumbers( 1,1 );
	}
	else
	{
		if ( bIsSearch ) pObject = MarketObject::GetSearchList( );
		else if ( bIsCart ) pObject = MarketObject::GetCartList( );
		else pObject = MarketObject::GetObjectList( );

		MarketObject **pSortedList = new MarketObject* [ iObjCount ];
		iObjCount = 0;

		while ( pObject )
		{
			if ( ( bShowPurchased || !pObject->IsPurchased() ) && ( bIsSearch || bIsCart || iGroupID == -4 || pObject->GetGroupID( ) == iGroupID ) )
			{
				pSortedList [ iObjCount ] = pObject;
				iObjCount++;
			}

			pObject = pObject->pNextObject;
		}

		if ( szOrderBy && strlen( szOrderBy ) > 0 )
		{
			MarketObject::SetSortIndex( szOrderBy );

			::sort( pSortedList, pSortedList + iObjCount, cmpO );
		}

		//HZIP zpImages = OpenZip( "Files\\TGCStore\\TEMP\\Thumbnails.zip", NULL );
		//if ( !zpImages ) MessageBox( "Failed to open image zip" );
		//int count = 0;
		//int imageCount = 0;

		int start = 0;
		int end = iObjCount;
		if ( itemsperpage > 0 ) 
		{
			int iMaxPage = (iObjCount-1) / itemsperpage + 1;
			if ( page > iMaxPage ) page = iMaxPage;
			if ( page < 1 ) page = 1;

			if ( m_pParent ) m_pParent->SetPageNumbers( page, iMaxPage );

			if ( iObjCount > itemsperpage )
			{
				start = (page-1) * itemsperpage; 
				end = (page * itemsperpage);
				if ( end > iObjCount ) end = iObjCount;
			}
		}
		
		for ( int i = start; i < end; i++ )
		{
			pObject = pSortedList [ i ];

			try
			{
				if ( !pObject->GetThumbnail( ) ) throw 1;
			
				/*
				int iIndex = -1;
				ZRESULT result = FindZipItem( zpImages, pObject->GetThumbnail( ), true, &iIndex, NULL );
				if ( result != ZR_OK )
				{
					//char str [ 32 ];
					//sprintf_s( str, 32, "Error: %d", result );
					//MessageBox( str );
					//MessageBox( pObject->GetThumbnail( ) );
				}

				if ( iIndex < 0 ) throw 2;
				*/

				EnterCriticalSection( &theApp.m_csDirectoryChanges );

				SetCurrentDirectory( theApp.m_szDirectory );

				CString path = "Files\\TGCStore\\TEMP\\Thumbnails\\";
				path += pObject->GetThumbnail( );
				
				CImage image;
				HRESULT hr = image.Load( path );
				
				LeaveCriticalSection( &theApp.m_csDirectoryChanges );

				if ( FAILED(hr) )
				{
					if ( bNeedThumbnailUpdate ) sThumbnailsNeeded += ";";
					char szID [ 12 ];
					sprintf_s( szID, 12, "%d", pObject->GetID() );
					sThumbnailsNeeded += szID;
					bNeedThumbnailUpdate = true;
					throw 3;
				}

				CWindowDC wndDC( this );
				CDC dc;
				dc.CreateCompatibleDC( &wndDC );

				CBitmap	bitmap; bitmap.CreateBitmap( 64,64, 1, 32, NULL );
				CBitmap *oldBmp = dc.SelectObject( &bitmap );

				image.StretchBlt( dc.GetSafeHdc( ), 0,0, 64,64 );
				dc.SelectObject( oldBmp );

				m_Images.Add( &bitmap, (CBitmap*)NULL );
				//bitmap.DeleteObject( );

				InsertItem ( count, pObject->GetName( ), imageCount );
				if ( count <= MAX_ITEMS_PER_PAGE ) m_dwObjID [ count ] = pObject->GetID();
				count++;
				imageCount++;
			}
			catch ( int )
			{
				InsertItem ( count, pObject->GetName( ), iNoThumbnailIcon );
				if ( count <= MAX_ITEMS_PER_PAGE ) m_dwObjID [ count ] = pObject->GetID();
				count++;
			}
		}

		delete [] pSortedList;

//		CloseZip( zpImages );

		//SetCurrentDirectory( szOldDir );
	}

	if ( bNeedThumbnailUpdate && !bThumbnailsUpdate )
	{
		if ( m_pParent ) m_pParent->UpdateThumbnails( sThumbnailsNeeded );
	}

	SetRedraw( TRUE );
	Invalidate( );
	m_pParent->m_textNoItems.Invalidate();
}