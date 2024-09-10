HRESULT CMediaController::CreateBitmapForKeyFrame(BYTE* pPixelData, IMFMediaType* pMediaType)
{
    if(!pPixelData || !pMediaType)
    {
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;

    INT32 stride = 0;

    //Get the Frame size and stride through Media Type attributes

    CHECK_HR (hr = MFGetAttributeSize(pMediaType, MF_MT_FRAME_SIZE, &m_Width, &m_Height));

    CHECK_HR (pMediaType->GetUINT32(MF_MT_DEFAULT_STRIDE, (UINT32*)&stride)); 

    SAFE_DELETE(m_pBitmap);

    //Create the bitmap with the given size
    m_pBitmap = new Bitmap(m_Width, m_Height, (INT32)stride, PixelFormat32bppRGB, pPixelData);

    if(!m_pBitmap)
    {
        hr = E_OUTOFMEMORY;
        goto done;
    }
    else
    {
        //Bitmap was created, set the flag
        m_fHasTestMedia = TRUE;
        TRACE((L"Bitmap for the key frame created.\n"));
    }

done:
    LOG_MSG_IF_FAILED(L"Bitmap could not be created.\n", hr);

    return hr;
}