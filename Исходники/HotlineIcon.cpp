bool CHotlineIcon::LoadItem( CFile* pFile )
	{
	if ( m_pIconData )
		// Déjà chargée
		return true;

	if ( 0 == m_iFileOffset )
		// Offset 0 -> erreur
		return false;

	TRY
		{
		int y;
		struct {
			char awpx[4];
			unsigned __int16 iVersion;
			unsigned __int16 iPad2;
			unsigned __int32 iPad1;
			unsigned __int32 iOne;
			unsigned __int32 iRealWidth;
			unsigned __int32 iHeight;
			unsigned __int32 iWidthBytes;
			unsigned __int32 iB, iC, iD, iDataSize;
			unsigned char iRTrans, iGTrans, iBTrans, iATrans;
			unsigned __int32 iNumColors;
			unsigned __int32 iZero;
			unsigned char iNumBits, iF, iG, iH;
			unsigned __int16 iHasTrans, iZ;
			} IconHeader;

		pFile->Seek( m_iFileOffset, CFile::begin );
		ASSERT( sizeof( IconHeader ) == 64 );
		pFile->Read( &IconHeader, sizeof( IconHeader ) );
		if ( strncmp( IconHeader.awpx, "AWPX", 4 ) != 0 )
			{
			TRACE( "CHotlineDatFile : load icon failed !\n" );
			return false;
			}
		if ( INT16_FROM_BE( IconHeader.iVersion ) != 1 )
			{
			TRACE( "CHotlineDatFile : load icon failed !\n" );
			return false;
			}
		if ( IconHeader.iNumBits != 8 )
			{
			TRACE( "CHotlineDatFile : load icon failed !\n" );
			return false;
			}
		
		IconHeader.iHasTrans = INT16_FROM_BE( IconHeader.iHasTrans );

		m_iNumberColors = INT32_FROM_BE( IconHeader.iNumColors );
		m_iDataWidth = INT32_FROM_BE( IconHeader.iWidthBytes);
		m_iWidth = INT32_FROM_BE( IconHeader.iRealWidth );
		m_iHeight = INT32_FROM_BE( IconHeader.iHeight );

		if ( m_iWidth > 32 )
			{
			m_iIconOffset = m_iWidth / 2 - 17;
			m_iWidth = m_iWidth - m_iIconOffset;
			}

		m_pPalette = new PALETTEENTRY[ m_iNumberColors ];
		pFile->Read( m_pPalette, 4 * m_iNumberColors );

		if ( IconHeader.iHasTrans )
			{
			const unsigned char cRed = IconHeader.iRTrans;
			const unsigned char cGreen = IconHeader.iGTrans;
			const unsigned char cBlue = IconHeader.iBTrans;
			for ( int iColor = 0; iColor < m_iNumberColors; iColor++ )
				{
				if ( ( cRed == m_pPalette[ iColor ].peRed ) &&
					( cGreen == m_pPalette[ iColor ].peGreen ) &&
					( cBlue == m_pPalette[ iColor ].peBlue ) )
					{
					m_iTransparentIndex = iColor;
					break;
					}
				}
			}
	
		m_pIconData = new char*[ m_iHeight ];

		for ( y = 0; y < m_iHeight; y++ )
			{
			m_pIconData[ y ] = new char[ m_iDataWidth ];
			pFile->Read( m_pIconData[ y ], m_iDataWidth );
			}
		}
	CATCH( CFileException, e )
		{
		e->Delete( );
		TRACE( "HotlineDatFile : load icon failed !\n" );
		return false;
		}