//-----------------------------------------------------------------------------
// Name: CWaveFile::WriteMMIO()
// Desc: Support function for reading from a multimedia I/O stream
//       pwfxDest is the WAVEFORMATEX for this new wave file.
//       m_hmmio must be valid before calling.  This function uses it to
//       update m_ckRiff, and m_ck.
//-----------------------------------------------------------------------------
HRESULT WaveDecoder::WriteMMIO( WAVEFORMATEX* pwfxDest )
{
    DWORD dwFactChunk; // Contains the actual fact chunk. Garbage until WaveCloseWriteFile.
    MMCKINFO ckOut1;

    memset( &ckOut1, 0, sizeof(ckOut1) );

    dwFactChunk = ( DWORD )-1;

    // Create the output file RIFF chunk of form type 'WAVE'.
    m_ckRiff.fccType = mmioFOURCC( 'W', 'A', 'V', 'E' );
    m_ckRiff.cksize = 0;

    if( 0 != mmioCreateChunk( m_hmmio, &m_ckRiff, MMIO_CREATERIFF ) )
        //return DXTRACE_ERR( L"mmioCreateChunk", E_FAIL );
		return E_FAIL;

    // We are now descended into the 'RIFF' chunk we just created.
    // Now create the 'fmt ' chunk. Since we know the size of this chunk,
    // specify it in the MMCKINFO structure so MMIO doesn't have to seek
    // back and set the chunk size after ascending from the chunk.
    m_ck.ckid = mmioFOURCC( 'f', 'm', 't', ' ' );
    m_ck.cksize = sizeof( PCMWAVEFORMAT );

    if( 0 != mmioCreateChunk( m_hmmio, &m_ck, 0 ) )
        //return DXTRACE_ERR( L"mmioCreateChunk", E_FAIL );
		return E_FAIL;

    // Write the PCMWAVEFORMAT structure to the 'fmt ' chunk if its that type.
    if( pwfxDest->wFormatTag == WAVE_FORMAT_PCM )
    {
        if( mmioWrite( m_hmmio, ( HPSTR )pwfxDest,
                       sizeof( PCMWAVEFORMAT ) ) != sizeof( PCMWAVEFORMAT ) )
            //return DXTRACE_ERR( L"mmioWrite", E_FAIL );
			return E_FAIL;
    }
    else
    {
        // Write the variable length size.
        if( ( UINT )mmioWrite( m_hmmio, ( HPSTR )pwfxDest,
                               sizeof( *pwfxDest ) + pwfxDest->cbSize ) !=
            ( sizeof( *pwfxDest ) + pwfxDest->cbSize ) )
            //return DXTRACE_ERR( L"mmioWrite", E_FAIL );
			return E_FAIL;
    }

    // Ascend out of the 'fmt ' chunk, back into the 'RIFF' chunk.
    if( 0 != mmioAscend( m_hmmio, &m_ck, 0 ) )
        //return DXTRACE_ERR( L"mmioAscend", E_FAIL );
		return E_FAIL;

    // Now create the fact chunk, not required for PCM but nice to have.  This is filled
    // in when the close routine is called.
    ckOut1.ckid = mmioFOURCC( 'f', 'a', 'c', 't' );
    ckOut1.cksize = 0;

    if( 0 != mmioCreateChunk( m_hmmio, &ckOut1, 0 ) )
        //return DXTRACE_ERR( L"mmioCreateChunk", E_FAIL );
		return E_FAIL;

    if( mmioWrite( m_hmmio, ( HPSTR )&dwFactChunk, sizeof( dwFactChunk ) ) !=
        sizeof( dwFactChunk ) )
        //return DXTRACE_ERR( L"mmioWrite", E_FAIL );
		return E_FAIL;

    // Now ascend out of the fact chunk...
    if( 0 != mmioAscend( m_hmmio, &ckOut1, 0 ) )
        //return DXTRACE_ERR( L"mmioAscend", E_FAIL );
		return E_FAIL;

    return S_OK;
}