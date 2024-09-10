HRESULT CTranscoder::ConfigureVideoOutput()
{
    assert (m_pProfile);

    HRESULT hr = S_OK;

    IMFAttributes* pVideoAttrs = NULL;

    // Configure the video stream

    // Create a new attribute store.
    if (SUCCEEDED(hr))
    {
        hr = MFCreateAttributes( &pVideoAttrs, 5 );
    }

    // Set the encoder to be Windows Media video encoder, so that the appropriate MFTs are added to the topology.
    if (SUCCEEDED(hr))
    {
        hr = pVideoAttrs->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_WMV3);
    }

    // Set the frame rate.
    if (SUCCEEDED(hr))
    {
        hr = MFSetAttributeRatio(pVideoAttrs, MF_MT_FRAME_RATE, 30, 1);
    }

    //Set the frame size.
    if (SUCCEEDED(hr))
    {
        hr = MFSetAttributeSize(pVideoAttrs, MF_MT_FRAME_SIZE, 320, 240);   
    }

    //Set the pixel aspect ratio
    if (SUCCEEDED(hr))
    {
        hr = MFSetAttributeRatio(pVideoAttrs, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);
    }

    // Set the bit rate.
    if (SUCCEEDED(hr))
    {
        hr = pVideoAttrs->SetUINT32(MF_MT_AVG_BITRATE, 300000);
    }

    // Set the attribute store on the transcode profile.
    if (SUCCEEDED(hr))
    {
        hr = m_pProfile->SetVideoAttributes( pVideoAttrs );
    }

    SafeRelease(&pVideoAttrs);
    return hr;
}