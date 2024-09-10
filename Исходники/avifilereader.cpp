HRESULT CAVIFileReader::Read( IN     BYTE *pBuffer,
                              IN     LONG nBufferSize, 
                              IN OUT LONG *pBytesRead)
{
    
    
    //
    // don't return garbage
    //

    *pBytesRead = 0;


    //
    // fail if the file is not open
    //

    if (NULL == m_pWaveFormat)
    {

        //
        // file is not open
        //

        LogError("CAVIFileReader::Read file is not open");

        return E_FAIL;
    }



    HRESULT hr = E_FAIL;


    //
    // read data into the user-supplied buffer, starting with the current 
    // stream position
    //
    
    LONG nSamplesRead = 0;
    
    hr = AVIStreamRead(m_pAudioStream, 
                        m_nSamplesReadSoFar, 
                        AVISTREAMREAD_CONVENIENT, 
                        pBuffer,
                        nBufferSize,
                        pBytesRead,
                        &nSamplesRead);

    if (FAILED(hr))
    {
        LogError("CAVIFileReader::Read AVIStreamRead failed");

        *pBytesRead = 0;

        return hr;
    }

    
    //
    // keep track of how many samples we have read, so we know where 
    // to start next time
    //

    m_nSamplesReadSoFar += nSamplesRead;

    if (*pBytesRead == 0)
    {
        LogMessage("CAVIFileReader::Read no more data in the file");

        return S_FALSE;
    }


    LogMessage("CAVIFileReader::Read read %ld bytes (%ld samples)", 
                *pBytesRead, nSamplesRead);

    return S_OK;
}