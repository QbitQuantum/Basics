//
// GetStaticImage
//
// Return a copy of the current image in the video renderer
//
HRESULT CVideoText::GetStaticImage(long *pBufferSize,long *pDIBImage)
{
    NOTE("Entering GetStaticImage");

    IMediaSample *pMediaSample;
    pMediaSample = m_pRenderer->GetCurrentSample();
    RECT SourceRect;

    // Is there an image available

    if (pMediaSample == NULL)
        return E_UNEXPECTED;

    // Find a scaled source rectangle for the current bitmap

    m_pRenderer->m_DrawImage.GetSourceRect(&SourceRect);
    SourceRect = m_pRenderer->m_DrawImage.ScaleSourceRect(&SourceRect);
    VIDEOINFOHEADER *pVideoInfo = (VIDEOINFOHEADER *) m_pRenderer->m_mtIn.Format();

    // Call the base class helper method to do the work

    HRESULT hr = CopyImage(pMediaSample,        // Buffer containing image
                           pVideoInfo,          // Type representing bitmap
                           pBufferSize,         // Size of buffer for DIB
                           (BYTE*) pDIBImage,   // Data buffer for output
                           &SourceRect);        // Current source position

    pMediaSample->Release();
    return hr;

} // GetStaticImage