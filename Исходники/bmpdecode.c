static HRESULT BmpFrameDecode_ReadUncompressed(BmpFrameDecode* This)
{
    UINT bytesperrow;
    UINT width, height;
    UINT datasize;
    int bottomup;
    HRESULT hr;
    LARGE_INTEGER offbits;
    ULONG bytesread;

    if (This->bih.bV5Size == sizeof(BITMAPCOREHEADER))
    {
        BITMAPCOREHEADER *bch = (BITMAPCOREHEADER*)&This->bih;
        width = bch->bcWidth;
        height = bch->bcHeight;
        bottomup = 1;
    }
    else
    {
        width = This->bih.bV5Width;
        height = abs(This->bih.bV5Height);
        bottomup = (This->bih.bV5Height > 0);
    }

    /* row sizes in BMP files must be divisible by 4 bytes */
    bytesperrow = (((width * This->bitsperpixel)+31)/32)*4;
    datasize = bytesperrow * height;

    This->imagedata = HeapAlloc(GetProcessHeap(), 0, datasize);
    if (!This->imagedata) return E_OUTOFMEMORY;

    offbits.QuadPart = This->bfh.bfOffBits;
    hr = IStream_Seek(This->stream, offbits, STREAM_SEEK_SET, NULL);
    if (FAILED(hr)) goto fail;

    hr = IStream_Read(This->stream, This->imagedata, datasize, &bytesread);
    if (FAILED(hr) || bytesread != datasize) goto fail;

    if (bottomup)
    {
        This->imagedatastart = This->imagedata + (height-1) * bytesperrow;
        This->stride = -bytesperrow;
    }
    else
    {
        This->imagedatastart = This->imagedata;
        This->stride = bytesperrow;
    }
    return S_OK;

fail:
    HeapFree(GetProcessHeap(), 0, This->imagedata);
    This->imagedata = NULL;
    if (SUCCEEDED(hr)) hr = E_FAIL;
    return hr;
}