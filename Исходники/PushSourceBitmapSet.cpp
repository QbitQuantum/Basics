HRESULT CPushPinBitmapSet::GetMediaType(CMediaType *pMediaType)
{
    CAutoLock cAutoLock(m_pFilter->pStateLock());

    CheckPointer(pMediaType, E_POINTER);

    // If the bitmap files were not loaded, just fail here.
    if (!m_bFilesLoaded)
        return E_FAIL;

    // Allocate enough room for the VIDEOINFOHEADER and the color tables
    VIDEOINFOHEADER *pvi = 
        (VIDEOINFOHEADER*)pMediaType->AllocFormatBuffer(SIZE_PREHEADER + 
                                                        m_cbBitmapInfo[m_iCurrentBitmap]);
    if (pvi == 0) 
        return(E_OUTOFMEMORY);

    // Initialize the video info header
    ZeroMemory(pvi, pMediaType->cbFormat);   
    pvi->AvgTimePerFrame = m_rtFrameLength;

    // Copy the header info from the current bitmap
    memcpy(&(pvi->bmiHeader), m_pBmi[m_iCurrentBitmap], m_cbBitmapInfo[m_iCurrentBitmap]);

    // Set image size for use in FillBuffer
    pvi->bmiHeader.biSizeImage  = GetBitmapSize(&pvi->bmiHeader);

    // Clear source and target rectangles
    SetRectEmpty(&(pvi->rcSource)); // we want the whole image area rendered
    SetRectEmpty(&(pvi->rcTarget)); // no particular destination rectangle

    pMediaType->SetType(&MEDIATYPE_Video);
    pMediaType->SetFormatType(&FORMAT_VideoInfo);
    pMediaType->SetTemporalCompression(FALSE);

    // Work out the GUID for the subtype from the header info.
    const GUID SubTypeGUID = GetBitmapSubtype(&pvi->bmiHeader);
    pMediaType->SetSubtype(&SubTypeGUID);
    pMediaType->SetSampleSize(pvi->bmiHeader.biSizeImage);

    return S_OK;
}