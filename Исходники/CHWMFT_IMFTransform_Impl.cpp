HRESULT CHWMFT::GetOutputAvailableType(
    DWORD           dwOutputStreamID,
    DWORD           dwTypeIndex,
    IMFMediaType**  ppType)
{
    /*****************************************
    ** Todo: This function will return a media
    ** type at a given index. The SDK 
    ** implementation uses a static array of
    ** media types. Your MFT may want to use
    ** a dynamic array and modify the list 
    ** order depending on the MFTs state
    ** See http://msdn.microsoft.com/en-us/library/ms703812(v=VS.85).aspx
    *****************************************/

    HRESULT         hr      = S_OK;
    IMFMediaType*   pMT     = NULL;

    do
    {
        if(IsLocked() != FALSE)
        {
            hr = MF_E_TRANSFORM_ASYNC_LOCKED;
            break;
        }

        if(ppType == NULL)
        {
            hr = E_POINTER;
            break;
        }

        /*****************************************
        ** Todo: If your MFT supports more than one
        ** stream, make sure you modify
        ** MFT_MAX_STREAMS and adjust this function
        ** accordingly
        *****************************************/
        if(dwOutputStreamID >= MFT_MAX_STREAMS)
        {
            hr = MF_E_INVALIDSTREAMNUMBER;
            break;
        }

        /*****************************************
        ** Todo: Modify the accepted output list
        ** g_ppguidOutputTypes or use your own
        ** implementation of this function
        *****************************************/
        if(dwTypeIndex >= g_dwNumOutputTypes)
        {
            hr = MF_E_NO_MORE_TYPES;
            break;
        }

        {
            CAutoLock lock(&m_csLock);

            hr = MFCreateMediaType(&pMT);
            if(FAILED(hr))
            {
                break;
            }

            hr = pMT->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
            if(FAILED(hr))
            {
                break;
            }

            hr = pMT->SetGUID(MF_MT_SUBTYPE, *(g_ppguidOutputTypes[dwTypeIndex]));
            if(FAILED(hr))
            {
                break;
            }

            /*****************************************
            ** Todo: The following implementation
            ** forces a standard output resolution
            ** and framerate. Your MFT should set these
            ** values properly and update the Media
            ** Type as necessary after decoding the
            ** stream
            *****************************************/
            hr = MFSetAttributeSize(pMT, MF_MT_FRAME_SIZE, MFT_OUTPUT_WIDTH, MFT_OUTPUT_HEIGHT);
            if(FAILED(hr))
            {
                break;
            }

            hr = MFSetAttributeRatio(pMT, MF_MT_FRAME_RATE, MFT_FRAMERATE_NUMERATOR, MFT_FRAMERATE_DENOMINATOR);
            if(FAILED(hr))
            {
                break;
            }

            (*ppType) = pMT;
            (*ppType)->AddRef();
        }
    }while(false);

    SAFERELEASE(pMT);

    return hr;
}