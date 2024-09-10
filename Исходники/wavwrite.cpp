//-----------------------------------------------------------------------------
// Name: WaveStartDataRead()
// Desc: This routine has to be called before any data is written to the wave output file, via wavewritefile.  This
//       sets up the data to write, and creates the data chunk.
//-----------------------------------------------------------------------------
HRESULT WaveStartDataWrite( HMMIO* phmmioOut, MMCKINFO* pckOut,
                            MMIOINFO* pmmioinfoOut )
{
    // Create the 'data' chunk that holds the waveform samples.  
    pckOut->ckid = mmioFOURCC('d', 'a', 't', 'a');
    pckOut->cksize = 0;

    if( 0 != mmioCreateChunk( *phmmioOut, pckOut, 0 ) ) 
        return E_FAIL;
    
    if( 0 != mmioGetInfo( *phmmioOut, pmmioinfoOut, 0 ) )
        return E_FAIL;
    
    return S_OK;
}