void CLibraryMetaPanel::Update()
{
	CSingleLock pLock1( &Library.m_pSection, TRUE );
	CSingleLock pLock2( &m_pSection, TRUE );

	CLibraryListPtr pSel( GetViewSelection() );
	m_nSelected = pSel ? static_cast< int >( pSel->GetCount() ) : 0;

	// Show info for library files only
	CLibraryFile* pFirst = NULL;
	if ( m_nSelected )
	{
		const CLibraryListItem& pItem = pSel->GetHead();
		if ( pItem.Type == CLibraryListItem::LibraryFile )
			pFirst = Library.LookupFile( pItem );
		if ( pFirst == NULL ) m_nSelected = 0;
	}

	m_nIcon32 = m_nIcon48 = -1;

	if ( m_nSelected == 1 )
	{
		m_nIndex	= pFirst->m_nIndex;
		m_sName		= pFirst->m_sName;
		m_sPath		= pFirst->GetPath();
		m_sFolder	= pFirst->GetFolder();
		m_sSize		= Settings.SmartVolume( pFirst->GetSize() );
		m_sType		= ShellIcons.GetTypeString( m_sName );
		m_nIcon32	= ShellIcons.Get( pFirst->GetPath(), 32 );
		m_nIcon48	= ShellIcons.Get( pFirst->GetPath(), 48 );
		m_nRating	= pFirst->m_nRating;
	}
	else if ( m_nSelected > 1 )
	{
		CString strFormat;
		LoadString( strFormat, IDS_LIBPANEL_MULTIPLE_FILES );
		m_sName.Format( strFormat, m_nSelected );
		QWORD nSize = 0;

		m_sFolder	= pFirst->GetFolder();
		m_nIcon32	= ShellIcons.Get( pFirst->GetPath(), 32 );
		m_nIcon48	= ShellIcons.Get( pFirst->GetPath(), 48 );
		m_nRating	= 0;

		for ( POSITION pos = pSel->GetHeadPosition() ; pos ; )
		{
			CLibraryFile* pFile = Library.LookupFile( pSel->GetNext( pos ) );
			if ( pFile == NULL ) continue;

			nSize += pFile->GetSize() / 1024;

			if ( pFile->IsAvailable() && pFile->GetFolder().CompareNoCase( m_sFolder ) )
			{
				LoadString( m_sFolder, IDS_LIBPANEL_MULTIPLE_FOLDERS );
			}

			int nIcon = ShellIcons.Get( pFile->GetPath(), 48 );
			if ( nIcon != m_nIcon48 ) m_nIcon48 = -1;
			nIcon = ShellIcons.Get( pFile->GetPath(), 32 );
			if ( nIcon != m_nIcon32 ) m_nIcon32 = -1;
		}

		m_sSize = Settings.SmartVolume( nSize );
		m_sPath.Empty();
		m_sType.Empty();
	}

	m_pSchema = NULL;

	if ( pSel )
	{
		for ( POSITION pos = pSel->GetHeadPosition() ; pos ; )
		{
			const CLibraryListItem& pItem = pSel->GetNext( pos );
			if ( pItem.Type != CLibraryListItem::LibraryFile ) continue;
			CLibraryFile* pFile = Library.LookupFile( pItem );
			if ( pFile == NULL ) continue;
			m_pSchema = pFile->m_pSchema;
			if ( m_pSchema ) break;
		}
	}

	if ( m_pServiceData )
	{
		m_pMetadata->Setup( m_pServiceData );
	}
	else
	{
		m_pMetadata->Setup( m_pSchema );

		if ( m_pSchema && pSel )
		{
			for ( POSITION pos = pSel->GetHeadPosition() ; pos ; )
			{
				const CLibraryListItem& pItem = pSel->GetNext( pos );
				if ( pItem.Type != CLibraryListItem::LibraryFile ) continue;
				if ( CLibraryFile* pFile = Library.LookupFile( pItem ) )
				{
					if ( pFile->m_pMetadata != NULL &&
						m_pSchema->Equals( pFile->m_pSchema ) )
					{
						m_pMetadata->Combine( pFile->m_pMetadata );
					}
				}
			}
		}
	}

	m_pMetadata->CreateLinks();
	m_pMetadata->Clean( 4096 );

	CClientDC dc( this );
	if ( Settings.General.LanguageRTL )
		SetLayout( dc.m_hDC, LAYOUT_BITMAPORIENTATIONPRESERVED );
	SCROLLINFO pInfo;
	CRect rc;

	GetClientRect( &rc );

	int nThumbSize = min( max( rc.Height() - 16, 64 ), (int)Settings.Library.ThumbSize );

	int nHeight = 54 + m_pMetadata->Layout( &dc, rc.Width() - 24 - nThumbSize );

	pInfo.cbSize	= sizeof(pInfo);
	pInfo.fMask		= SIF_ALL & ~SIF_TRACKPOS;
	pInfo.nMin		= 0;
	pInfo.nMax		= nHeight;
	pInfo.nPage		= rc.Height();
	pInfo.nPos		= GetScrollPos( SB_VERT );
	pInfo.nPos		= max( 0, min( pInfo.nPos, pInfo.nMax - (int)pInfo.nPage + 1 ) );

	SetScrollInfo( SB_VERT, &pInfo, TRUE );

	if ( m_bForceUpdate || ( m_sThumb != m_sPath ) )
	{
		m_bForceUpdate = FALSE;

		if ( m_bmThumb.m_hObject )
			m_bmThumb.DeleteObject();

		if ( ! IsThreadAlive() )
		{
			BeginThread( "CtrlLibraryMetaPanel" );
		}
	}

	pLock2.Unlock();
	pLock1.Unlock();

	Invalidate();
}