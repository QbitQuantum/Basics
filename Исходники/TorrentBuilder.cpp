BOOL CTorrentBuilder::ProcessFile(DWORD nFile, LPCTSTR pszFile)
{
    m_pSection.Lock();
    m_sThisFile = pszFile;
    m_pSection.Unlock();

    LPCTSTR szFilepath = ( _tcsclen( pszFile ) < MAX_PATH ) ?
                         pszFile : (LPCTSTR)( CString( _T("\\\\?\\") ) + pszFile );

    HANDLE hFile = CreateFile( szFilepath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
    if ( hFile == INVALID_HANDLE_VALUE )
        return FALSE;

    DWORD nLow, nHigh;
    nLow = GetFileSize( hFile, &nHigh );
    QWORD nSize = ( (QWORD)nHigh << 32 ) + (QWORD)nLow;

    if ( m_bSHA1 ) m_pFileSHA1[ nFile ].Reset();
    if ( m_bED2K ) m_pFileED2K[ nFile ].BeginFile( nSize );
    if ( m_bMD5 )  m_pFileMD5[ nFile ].Reset();

    while ( nSize > 0 && ! m_bAbort )
    {
        DWORD nLimit = min( m_nBuffer, m_nPieceSize - m_nPieceUsed );
        DWORD nRead  = ( nSize > (QWORD)nLimit ) ? nLimit : (DWORD)nSize;

        if ( ! ReadFile( hFile, m_pBuffer, nRead, &nRead, NULL ) || nRead == 0 )
            break;

        nSize -= (QWORD)nRead;
        m_nTotalPos += (QWORD)nRead;

        m_oPieceSHA1.Add( m_pBuffer, nRead );
        m_nPieceUsed += nRead;

        if ( m_bSHA1 )
        {
            m_oDataSHA1.Add( m_pBuffer, nRead );
            m_pFileSHA1[ nFile ].Add( m_pBuffer, nRead );
        }

        if ( m_bED2K )
        {
            m_oDataED2K.AddToFile( m_pBuffer, nRead );
            m_pFileED2K[ nFile ].AddToFile( m_pBuffer, nRead );
        }

        if ( m_bMD5 )
        {
            m_oDataMD5.Add( m_pBuffer, nRead );
            m_pFileMD5[ nFile ].Add( m_pBuffer, nRead );
        }

        if ( m_nPieceUsed >= m_nPieceSize )
        {
            m_oPieceSHA1.Finish();
            m_pPieceSHA1[ m_nPiecePos++ ] = m_oPieceSHA1;
            m_oPieceSHA1.Reset();
            m_nPieceUsed = 0;
        }
    }

    if ( m_bSHA1 ) m_pFileSHA1[ nFile ].Finish();
    if ( m_bED2K ) m_pFileED2K[ nFile ].FinishFile();
    if ( m_bMD5 )  m_pFileMD5[ nFile ].Finish();

    CloseHandle( hFile );

    return ( nSize == 0 );
}