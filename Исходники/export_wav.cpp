//-----------------------------------------------------------------------------
// Name: CWaveFile::Open()
// Desc: Opens a wave file for reading
//-----------------------------------------------------------------------------
HRESULT CWaveFile::Open( LPSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags )
{
    HRESULT hr;

    m_dwFlags = dwFlags;
    m_bIsReadingFromMemory = FALSE;

    if( m_dwFlags == WAVEFILE_READ )
    {
        if( strFileName == NULL )
            return E_INVALIDARG;
        SAFE_DELETE_ARRAY( m_pwfx );

        m_hmmio = mmioOpen( strFileName, NULL, MMIO_ALLOCBUF | MMIO_READ );

        if( FAILED( hr = ReadMMIO() ) )
        {
            // ReadMMIO will fail if its an not a wave file
            mmioClose( m_hmmio, 0 );
            return WAVEFILE_ERROR( L"ReadMMIO", hr );
        }

        if( FAILED( hr = ResetFile() ) )
            return WAVEFILE_ERROR( L"ResetFile", hr );

        // After the reset, the size of the wav file is m_ck.cksize so store it now
        m_dwSize = m_ck.cksize;
    }
    else
    {
        m_hmmio = mmioOpen( strFileName, NULL, MMIO_ALLOCBUF  |
                                                  MMIO_READWRITE |
                                                  MMIO_CREATE );
        if( NULL == m_hmmio )
            return WAVEFILE_ERROR( L"mmioOpen", E_FAIL );

        if( FAILED( hr = WriteMMIO( pwfx ) ) )
        {
            mmioClose( m_hmmio, 0 );
            return WAVEFILE_ERROR( L"WriteMMIO", hr );
        }

        if( FAILED( hr = ResetFile() ) )
            return WAVEFILE_ERROR( L"ResetFile", hr );
    }

    return hr;
}