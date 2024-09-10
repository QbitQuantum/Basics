HRESULT DrawDevice::SetVideoType(IMFMediaType *pType)
{
    HRESULT hr = S_OK;
    GUID subtype = { 0 };
    MFRatio PAR = { 0 };

    // Find the video subtype.
    hr = pType->GetGUID(MF_MT_SUBTYPE, &subtype);

    if (FAILED(hr)) { goto done; }

    // Choose a conversion function.
    // (This also validates the format type.)

    hr = SetConversionFunction(subtype); 
    
    if (FAILED(hr)) { goto done; }

    //
    // Get some video attributes.
    //

    // Get the frame size.
    hr = MFGetAttributeSize(pType, MF_MT_FRAME_SIZE, &m_width, &m_height);
    
    if (FAILED(hr)) { goto done; }

    
    // Get the interlace mode. Default: assume progressive.
    m_interlace = (MFVideoInterlaceMode)MFGetAttributeUINT32(
        pType,
        MF_MT_INTERLACE_MODE, 
        MFVideoInterlace_Progressive
        );

    // Get the image stride.
    hr = GetDefaultStride(pType, &m_lDefaultStride);

    if (FAILED(hr)) { goto done; }

    // Get the pixel aspect ratio. Default: Assume square pixels (1:1)
    hr = MFGetAttributeRatio(
        pType, 
        MF_MT_PIXEL_ASPECT_RATIO, 
        (UINT32*)&PAR.Numerator, 
        (UINT32*)&PAR.Denominator
        );

    if (SUCCEEDED(hr))
    {
        m_PixelAR = PAR;
    }
    else
    {
        m_PixelAR.Numerator = m_PixelAR.Denominator = 1;
    }

    m_format = (D3DFORMAT)subtype.Data1;

    // Create Direct3D swap chains.

    hr = CreateSwapChains();

    if (FAILED(hr)) { goto done; }


    // Update the destination rectangle for the correct
    // aspect ratio.

    UpdateDestinationRect();

	if (m_pBuf) delete [] m_pBuf;
	m_pBuf = new BYTE[m_height * m_width * 3];

done:
    if (FAILED(hr))
    {
        m_format = D3DFMT_UNKNOWN;
        m_convertFn = NULL;
    }
    return hr;
}