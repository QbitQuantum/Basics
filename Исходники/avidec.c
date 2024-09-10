static HRESULT WINAPI AVIDec_SetMediaType(TransformFilter *tf, PIN_DIRECTION dir, const AM_MEDIA_TYPE * pmt)
{
    AVIDecImpl* This = (AVIDecImpl*)tf;
    HRESULT hr = VFW_E_TYPE_NOT_ACCEPTED;

    TRACE("(%p)->(%p)\n", This, pmt);

    if (dir != PINDIR_INPUT)
        return S_OK;

    /* Check root (GUID w/o FOURCC) */
    if ((IsEqualIID(&pmt->majortype, &MEDIATYPE_Video)) &&
        (!memcmp(((const char *)&pmt->subtype)+4, ((const char *)&MEDIATYPE_Video)+4, sizeof(GUID)-4)))
    {
        VIDEOINFOHEADER *format1 = (VIDEOINFOHEADER *)pmt->pbFormat;
        VIDEOINFOHEADER2 *format2 = (VIDEOINFOHEADER2 *)pmt->pbFormat;
        BITMAPINFOHEADER *bmi;

        if (IsEqualIID(&pmt->formattype, &FORMAT_VideoInfo))
            bmi = &format1->bmiHeader;
        else if (IsEqualIID(&pmt->formattype, &FORMAT_VideoInfo2))
            bmi = &format2->bmiHeader;
        else
            goto failed;
        TRACE("Fourcc: %s\n", debugstr_an((const char *)&pmt->subtype.Data1, 4));

        This->hvid = ICLocate(pmt->majortype.Data1, pmt->subtype.Data1, bmi, NULL, ICMODE_DECOMPRESS);
        if (This->hvid)
        {
            AM_MEDIA_TYPE* outpmt = &This->tf.pmt;
            const CLSID* outsubtype;
            DWORD bih_size;
            DWORD output_depth = bmi->biBitCount;
            DWORD result;
            FreeMediaType(outpmt);

            switch(bmi->biBitCount)
            {
                case 32: outsubtype = &MEDIASUBTYPE_RGB32; break;
                case 24: outsubtype = &MEDIASUBTYPE_RGB24; break;
                case 16: outsubtype = &MEDIASUBTYPE_RGB565; break;
                case 8:  outsubtype = &MEDIASUBTYPE_RGB8; break;
                default:
                    WARN("Non standard input depth %d, forced output depth to 32\n", bmi->biBitCount);
                    outsubtype = &MEDIASUBTYPE_RGB32;
                    output_depth = 32;
                    break;
            }

            /* Copy bitmap header from media type to 1 for input and 1 for output */
            bih_size = bmi->biSize + bmi->biClrUsed * 4;
            This->pBihIn = CoTaskMemAlloc(bih_size);
            if (!This->pBihIn)
            {
                hr = E_OUTOFMEMORY;
                goto failed;
            }
            This->pBihOut = CoTaskMemAlloc(bih_size);
            if (!This->pBihOut)
            {
                hr = E_OUTOFMEMORY;
                goto failed;
            }
            memcpy(This->pBihIn, bmi, bih_size);
            memcpy(This->pBihOut, bmi, bih_size);

            /* Update output format as non compressed bitmap */
            This->pBihOut->biCompression = 0;
            This->pBihOut->biBitCount = output_depth;
            This->pBihOut->biSizeImage = This->pBihOut->biWidth * This->pBihOut->biHeight * This->pBihOut->biBitCount / 8;
            TRACE("Size: %u\n", This->pBihIn->biSize);
            result = ICDecompressQuery(This->hvid, This->pBihIn, This->pBihOut);
            if (result != ICERR_OK)
            {
                ERR("Unable to found a suitable output format (%d)\n", result);
                goto failed;
            }

            /* Update output media type */
            CopyMediaType(outpmt, pmt);
            outpmt->subtype = *outsubtype;

            if (IsEqualIID(&pmt->formattype, &FORMAT_VideoInfo))
                memcpy(&(((VIDEOINFOHEADER *)outpmt->pbFormat)->bmiHeader), This->pBihOut, This->pBihOut->biSize);
            else if (IsEqualIID(&pmt->formattype, &FORMAT_VideoInfo2))
                memcpy(&(((VIDEOINFOHEADER2 *)outpmt->pbFormat)->bmiHeader), This->pBihOut, This->pBihOut->biSize);
            else
                assert(0);

            TRACE("Connection accepted\n");
            return S_OK;
        }
        TRACE("Unable to find a suitable VFW decompressor\n");
    }

failed:

    TRACE("Connection refused\n");
    return hr;
}