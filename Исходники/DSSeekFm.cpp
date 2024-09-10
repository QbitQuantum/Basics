//------------------------------------------------------------------------------
// Name: IsFrameSeekable()
// Desc: Ascertains whether the file contains a stream that is seekable by frame.
//       If so, the method returns the stream number and the number of frames.
//
// wszFile:           Specifies the file name.
// ppSyncReader:      Receives a pointer to the synchronous reader's IWMSyncReader 
//                    interface.
// pwFrameSeekStream: Receives the stream number of the seekable stream.
// pqqTotalFrames:    Receives the number of frames in the stream.
//------------------------------------------------------------------------------
BOOL IsFrameSeekable( LPCWSTR wszFile, IWMSyncReader ** ppSyncReader, 
                      WORD *pwFrameSeekStream, QWORD *pqwTotalFrames )
{
    if( !ppSyncReader || !pwFrameSeekStream )
        return FALSE;

    HRESULT hr = E_FAIL;

    // Create a synchronous reader and load the specified file.
    hr = WMCreateSyncReader( 0, 0, ppSyncReader );
    if( FAILED( hr ) )
    {
        _tprintf(_T("Couldn't create the synchronous reader for ASF frame seeking! hr=0x%x\nPlayback aborted.\n\n"), hr);
    } 
    
    if( SUCCEEDED( hr ) )
    {
        // Open the source file.
        hr = (*ppSyncReader)->Open( wszFile );
        if( FAILED( hr ) )
        {
            _tprintf(_T("WMSDK Sync reader failed to open file! hr=0x%x\nPlayback aborted.\n\n"), hr);
        }
    }

    if( SUCCEEDED( hr ) )
    {
        CComPtr <IWMProfile> pProfile;

        hr = (*ppSyncReader)->QueryInterface( IID_IWMProfile, (void **) &pProfile );
        if( SUCCEEDED( hr ) ) 
        {

            // Loop through each stream and check the "NumberOfFrames" attribute in the 
            // ASF header for that stream number. This attribute is present if the stream
            // has been indexed by frame.

            DWORD cStreams;
            WORD wStreamNum;

            // Get the number of streams.
            hr = pProfile->GetStreamCount(&cStreams);
            if( SUCCEEDED( hr ) )
            {
                for( DWORD dw = 0; dw < cStreams; dw++ )
                {
                    CComPtr <IWMStreamConfig> pConfig;

                    hr = pProfile->GetStream( dw, &pConfig );
                    if( SUCCEEDED( hr ) )
                    {
                        // Get the stream number for this stream. 
                        hr = pConfig->GetStreamNumber( &wStreamNum );
                        if( SUCCEEDED( hr ) )
                        {
                            CComPtr <IWMHeaderInfo> pWMHI;

                            hr = (*ppSyncReader)->QueryInterface( IID_IWMHeaderInfo, (void **) &pWMHI );
                            if( SUCCEEDED( hr ) )
                            {
                                // Check whether the header contains a "NumberOfFrames" attribute 
                                // (g_wszWMNumberOfFrames) for this stream. If so, the value of the
                                // attribute is the number of frames in the stream.

                                WMT_ATTR_DATATYPE Type;
                                QWORD qwFrames;
                                WORD cbLength = sizeof(qwFrames);

                                hr = pWMHI->GetAttributeByName(&wStreamNum,
                                                               g_wszWMNumberOfFrames,
                                                               &Type,
                                                               (BYTE *) &qwFrames,
                                                               &cbLength);
                                if( SUCCEEDED( hr ) ) 
                                {
                                    // This stream is seekable by frame. Return the stream number
                                    // and the number of frames.
                                    *pwFrameSeekStream = wStreamNum;
                                    *pqwTotalFrames = qwFrames;
                                } 
                            }
                        }
                    }
                }
            }
        }
    }

    return ( S_OK == hr );
}