STDMETHODIMP CDataCallback::BandedDataCallback(
    LONG   lReason,
    LONG   lStatus,
    LONG   lPercentComplete,
    LONG   lOffset,
    LONG   lLength,
    LONG, LONG,
    PBYTE  pbBuffer
)
{
    HRESULT hr;

    // Parse the message

    switch (lReason)
    {
        case IT_MSG_DATA_HEADER:
        {
            PWIA_DATA_CALLBACK_HEADER pHeader = (PWIA_DATA_CALLBACK_HEADER) pbBuffer;

            // Determine if this is a BMP transfer

            m_bBMP = pHeader->guidFormatID == WiaImgFmt_MEMORYBMP || pHeader->guidFormatID == WiaImgFmt_BMP;

            // For WiaImgFmt_MEMORYBMP transfers, WIA does not send a BITMAPFILEHEADER before the data.
            // In this program, we desire all BMP files to contain a BITMAPFILEHEADER, so add it manually

            m_nHeaderSize = pHeader->guidFormatID == WiaImgFmt_MEMORYBMP ? sizeof(BITMAPFILEHEADER) : 0;

            // Allocate memory for the image if the size is given in the header

            if (pHeader != NULL && pHeader->lBufferSize != 0)
            {
                hr = ReAllocBuffer(m_nHeaderSize + pHeader->lBufferSize);

                if (FAILED(hr))
                {
                    return hr;
                }
            }
        
            break;
        }

        case IT_MSG_DATA:
        {
            // Invoke the callback function

            hr = m_pfnProgressCallback(lStatus, lPercentComplete, m_pProgressCallbackParam);

            if (FAILED(hr) || hr == S_FALSE)
            {
                return hr;
            }

            // If the buffer is not allocated yet and this is the first block, 
            // and the transferred image is in BMP format, allocate the buffer
            // according to the size information in the bitmap header

            if (m_pStream == NULL && lOffset == 0 && m_bBMP)
            {
                LONG nBufferSize = BitmapUtil::GetBitmapSize(pbBuffer);

                if (nBufferSize != 0)
                {
                    hr = ReAllocBuffer(m_nHeaderSize + nBufferSize);

                    if (FAILED(hr))
                    {
                        return hr;
                    }
                }
            }

            if (m_nHeaderSize + lOffset + lLength < 0)
            {
                return E_OUTOFMEMORY;
            }

            // If the transfer goes past the buffer, try to expand it
            if (m_nHeaderSize + lOffset + lLength > m_nDataSize)
            {
                hr = ReAllocBuffer(m_nHeaderSize + lOffset + lLength);

                if (FAILED(hr))
                {
                    return hr;
                }
            }

            // copy the transfer buffer

            hr = CopyToBuffer(m_nHeaderSize + lOffset, pbBuffer, lLength);

            if (FAILED(hr))
            {
                return hr;
            }

            break;
        }

        case IT_MSG_STATUS:
        {
            // Invoke the callback function

            hr = m_pfnProgressCallback(lStatus, lPercentComplete, m_pProgressCallbackParam);

            if (FAILED(hr) || hr == S_FALSE)
            {
                return hr;
            }

            break;
        }

        case IT_MSG_TERMINATION:
        case IT_MSG_NEW_PAGE:
        {
            if (m_pStream != NULL)
            {
                // For BMP files, we should validate the the image header
                // So, obtain the memory buffer from the stream

                if (m_bBMP)
                {
                    // Since the stream is created using CreateStreamOnHGlobal,
                    // we can get the memory buffer with GetHGlobalFromStream.

                    HGLOBAL hBuffer;

                    hr = GetHGlobalFromStream(m_pStream, &hBuffer);

                    if (FAILED(hr))
                    {
                        return hr;
                    }

                    PBITMAPFILEHEADER pBuffer = (PBITMAPFILEHEADER) GlobalLock(hBuffer);

                    if (pBuffer == NULL)
                    {
                        return HRESULT_FROM_WIN32(GetLastError());
                    }

                    // Some scroll-fed scanners may return 0 as the bitmap height
                    // In this case, calculate the image height and modify the header

                    BitmapUtil::FixBitmapHeight(pBuffer + 1, m_nDataSize, TRUE);

                    // For WiaImgFmt_MEMORYBMP transfers, the WIA service does not 
                    // include a BITMAPFILEHEADER preceeding the bitmap data. 
                    // In this case, fill in the BITMAPFILEHEADER structure.
        
                    if (m_nHeaderSize != 0)
                    {
                        BitmapUtil::FillBitmapFileHeader(pBuffer + 1, pBuffer);
                    }

                    GlobalUnlock(hBuffer);
                }

                // Store this buffer in the successfully transferred images array

                hr = StoreBuffer();

                if (FAILED(hr))
                {
                    return hr;
                }
            }

            break;
        }
    }

    return S_OK;
}