//-----------------------------------------------------------------------------
// Name: CHMWaveFile::ResetFile()
// Desc: Resets the internal m_ck pointer so reading starts from the 
//       beginning of the file again 
//-----------------------------------------------------------------------------
HRESULT CHMWaveFile::ResetFile()
{
    if( m_bIsReadingFromMemory )
    {
        m_pbDataCur = m_pbData;
    }
    else 
    {
        if( m_hmmio == NULL )
            return CO_E_NOTINITIALIZED;

        if( m_dwFlags == WAVEFILE_READ )
        {
            // Seek to the data
            if( -1 == mmioSeek( m_hmmio, m_ckRiff.dwDataOffset + sizeof(FOURCC),
                            SEEK_SET ) )
                //return DXTRACE_ERR( TEXT("mmioSeek"), E_FAIL );
				return -1;

            // Search the input file for the 'data' chunk.
            m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
            if( 0 != mmioDescend( m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK ) )
              //return DXTRACE_ERR( TEXT("mmioDescend"), E_FAIL );
			  return -1;
        }
        else
        {
            // Create the 'data' chunk that holds the waveform samples.  
            m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
            m_ck.cksize = 0;

            if( 0 != mmioCreateChunk( m_hmmio, &m_ck, 0 ) ) 
                //return DXTRACE_ERR( TEXT("mmioCreateChunk"), E_FAIL );
				return -1;

            if( 0 != mmioGetInfo( m_hmmio, &m_mmioinfoOut, 0 ) )
                //return DXTRACE_ERR( TEXT("mmioGetInfo"), E_FAIL );
				return -1;
        }
    }
    
    return S_OK;
}