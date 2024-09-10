HRESULT PackedResource::Create( const char *strFilename )
#endif
{
#ifdef _XBOX1
    BOOL bHasResourceOffsetsTable = FALSE;

    // Find the media file
    CHAR strResourcePath[512];
    if( FAILED(FindMediaFile(strResourcePath, strFilename, sizeof(strResourcePath))))
        return E_FAIL;
    else
        strFilename = strResourcePath;
#endif

    // Open the file
    HANDLE hFile;
    DWORD dwNumBytesRead;
    hFile = CreateFile( strFilename, GENERIC_READ, FILE_SHARE_READ, NULL,
                               OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL );
    if( hFile == INVALID_HANDLE_VALUE )
    {
        RARCH_ERR( "PackedResource::Create(): File <%s> not found.\n", strFilename );
        return E_FAIL;
    }

    // Read in and verify the XPR magic header
    XPR_HEADER xprh;
    bool retval = ReadFile( hFile, &xprh, sizeof( XPR_HEADER ), &dwNumBytesRead, NULL );

#if defined(_XBOX1)
    if( xprh.dwMagic == XPR0_MAGIC_VALUE )
    {
        bHasResourceOffsetsTable = FALSE;
    }
    else if( xprh.dwMagic == XPR1_MAGIC_VALUE )
    {
        bHasResourceOffsetsTable = TRUE;
    }
    else
#elif defined(_XBOX360)
    if(!retval)
    {
        RARCH_ERR("Error reading XPR header in file %s.\n", strFilename );
        CloseHandle( hFile );
        return E_FAIL;
    }

    if( xprh.dwMagic != XPR2_MAGIC_VALUE )
#endif
    {
        RARCH_ERR( "Invalid Xbox Packed Resource (.xpr) file: Magic = 0x%08lx\n", xprh.dwMagic );
        CloseHandle( hFile );
        return E_FAIL;
    }

    // Compute memory requirements
#if defined(_XBOX1)
    m_dwSysMemDataSize = xprh.dwHeaderSize - sizeof(XPR_HEADER);
    m_dwVidMemDataSize = xprh.dwTotalSize - xprh.dwHeaderSize;
#elif defined(_XBOX360)
    m_dwSysMemDataSize = xprh.dwHeaderSize;
    m_dwVidMemDataSize = xprh.dwDataSize;
#endif

    // Allocate memory
    m_pSysMemData = (BYTE*)malloc(m_dwSysMemDataSize);
    if( m_pSysMemData == NULL )
    {
        RARCH_ERR( "Could not allocate system memory.\n" );
        m_dwSysMemDataSize = 0;
        return E_FAIL;
    }

    m_pVidMemData = ( BYTE* )AllocateContiguousMemory( m_dwVidMemDataSize,
#if defined(_XBOX1)
D3DTEXTURE_ALIGNMENT
#elif defined(_XBOX360)
XALLOC_PHYSICAL_ALIGNMENT_4K
#endif
    );

    if( m_pVidMemData == NULL )
    {
        RARCH_ERR( "Could not allocate physical memory.\n" );
        m_dwSysMemDataSize = 0;
        m_dwVidMemDataSize = 0;
        free(m_pSysMemData);
        m_pSysMemData = NULL;
        return E_FAIL;
    }

    // Read in the data from the file
    if( !ReadFile( hFile, m_pSysMemData, m_dwSysMemDataSize, &dwNumBytesRead, NULL ) ||
        !ReadFile( hFile, m_pVidMemData, m_dwVidMemDataSize, &dwNumBytesRead, NULL ) )
    {
        RARCH_ERR( "Unable to read Xbox Packed Resource (.xpr) file\n" );
        CloseHandle( hFile );
        return E_FAIL;
    }

    // Done with the file
    CloseHandle( hFile );

#ifdef _XBOX1
    if (bHasResourceOffsetsTable)
    {
#endif

    // Extract resource table from the header data
    m_dwNumResourceTags = *( DWORD* )( m_pSysMemData + 0 );
    m_pResourceTags = ( XBRESOURCE* )( m_pSysMemData + 4 );

    // Patch up the resources
    for( DWORD i = 0; i < m_dwNumResourceTags; i++ )
    {
        m_pResourceTags[i].strName = ( CHAR* )( m_pSysMemData + ( DWORD )m_pResourceTags[i].strName );
#ifdef _XBOX360
        // Fixup the texture memory
        if( ( m_pResourceTags[i].dwType & 0xffff0000 ) == ( RESOURCETYPE_TEXTURE & 0xffff0000 ) )
        {
            D3DTexture* pTexture = ( D3DTexture* )&m_pSysMemData[m_pResourceTags[i].dwOffset];

            // Adjust Base address according to where memory was allocated
            XGOffsetBaseTextureAddress( pTexture, m_pVidMemData, m_pVidMemData );
        }
#endif
    }

#ifdef _XBOX1
    }
#endif

#ifdef _XBOX1
    // Use user-supplied number of resources and the resource tags
    if( dwNumResourceTags != 0 || pResourceTags != NULL )
    {
        m_pResourceTags     = pResourceTags;
        m_dwNumResourceTags = dwNumResourceTags;
    }
#endif

    m_bInitialized = TRUE;

    return S_OK;
}